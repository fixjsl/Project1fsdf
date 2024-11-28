#include "Header.h"
#include "ICMP.h"



//private

	//무결성검사를 위한 체크섬 생성함수
	uint16_t ICMP::CalculateChecksum(uint16_t* buffer, int size) {
		uint32_t checksum = 0;
		while (size > 1)
		{
			checksum += *buffer++;
			size -= 2;
		}
		if (size == 1) {
			checksum += *(uint8_t*)buffer;
		}

		checksum = (checksum & 0xFFFF) + (checksum >> 16);
		checksum += (checksum >> 16);

		return (uint16_t)~checksum;

	}
	// 패킷과 현재 패킷 생성 번호를 받아 패킷을 초기화 하고 리턴
	void ICMP::CreatePacket(ICMPHEADER& icmp, uint16_t crseq) {
		memset(&icmp, 0, sizeof(ICMPHEADER));
		icmp.Type = 8;
		icmp.Code = 0;
		icmp.id = (uint16_t)GetCurrentProcessId();
		icmp.sequence = crseq;
		icmp.Checksum = 0;
		icmp.Checksum = CalculateChecksum((uint16_t*)&icmp, sizeof(icmp));
	}
	//패킷 분석 함수
	sockaddr_in ICMP::Stadd(std::string destAddr)
	{
		sockaddr_in destip;
		
		memset(&destip, 0, sizeof(destip));
		
		destip.sin_family = AF_INET;
		if (inet_pton(AF_INET, destAddr.c_str(), &destip.sin_addr) != 1) {
			const char* domain = destAddr.c_str();
			struct addrinfo hint, *result;
			sockaddr_in* Domaindestip;
			memset(&Domaindestip, 0, sizeof(Domaindestip));
			memset(&hint, 0, sizeof(hint));
			hint.ai_family = AF_INET;
			hint.ai_socktype = SOCK_RAW;
			Domaindestip->sin_family = AF_INET;

			int red = getaddrinfo(destAddr.c_str(), NULL, &hint, &result);
			if (red != 0) {
				ICMPError = "invalid domain";
			}
			Domaindestip = (sockaddr_in*)result->ai_addr;
			return *Domaindestip;
		}
		return destip;
	}
	//문자열 ip변환 함수


	//public
	
	//송신함수
	std::string ICMP::Send(SOCKET sock, int ttl,std::string destAddr) {
		

		ICMPHEADER icmp;
		//문자열을 ip주소로 변환
		sockaddr_in destip = Stadd(destAddr);
		
		//패킷 생성	
		CreatePacket(icmp, ttl * 10);
		setsockopt(sock, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl));
		//패킷 송신 및 오류검사
		if (sendto(sock, (char*)&icmp, sizeof(icmp), 0, (struct sockaddr*)&destip, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			std::cerr << "Failed send to Packet" << "\n";
			if (WSAGetLastError() == EPERM) {
				return GrantError = "관리자 권한으로 재실행 요구";
			}
		}
		else {
			std::cout << "Send Success" << std::endl;
		}
		return "";
	}
	std::string ICMP::Receive(SOCKET sock) {
		
		int ipsize = sizeof(ipadd);
		//수신받은 패킷의 데이터와 ip주소 저장

		
		int result = recvfrom(sock,rebuff,sizeof(rebuff),0,(sockaddr*)&ipadd,&ipsize);
		if (result == -1) {
			RecvError = "TIME OUT ERROR";
			return RecvError;
		}
		else {
			std::cout << "Recv Success" << std::endl;
			inet_ntop(AF_INET, &ipadd.sin_addr, ip, INET_ADDRSTRLEN);
			std::cout << "ip = " << ip << std::endl;
		}
			
		
		
		return "";
		
	}

	std::string ICMP::getIp()
	{
		return ip;
	}

	uint8_t ICMP::getType()
	{
		return type;
	}
	