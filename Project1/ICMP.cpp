#include "Header.h"
#include "ICMP.h"



//private

	//���Ἲ�˻縦 ���� üũ�� �����Լ�
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
	// ��Ŷ�� ���� ��Ŷ ���� ��ȣ�� �޾� ��Ŷ�� �ʱ�ȭ �ϰ� ����
	void ICMP::CreatePacket(ICMPHEADER& icmp, uint16_t crseq) {
		memset(&icmp, 0, sizeof(ICMPHEADER));
		icmp.Type = 8;
		icmp.Code = 0;
		icmp.id = (uint16_t)GetCurrentProcessId();
		icmp.sequence = crseq;
		icmp.Checksum = 0;
		icmp.Checksum = CalculateChecksum((uint16_t*)&icmp, sizeof(icmp));
	}
	//��Ŷ �м� �Լ�
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
	//���ڿ� ip��ȯ �Լ�


	//public
	
	//�۽��Լ�
	std::string ICMP::Send(SOCKET sock, int ttl,std::string destAddr) {
		

		ICMPHEADER icmp;
		//���ڿ��� ip�ּҷ� ��ȯ
		sockaddr_in destip = Stadd(destAddr);
		
		//��Ŷ ����	
		CreatePacket(icmp, ttl * 10);
		setsockopt(sock, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl));
		//��Ŷ �۽� �� �����˻�
		if (sendto(sock, (char*)&icmp, sizeof(icmp), 0, (struct sockaddr*)&destip, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			std::cerr << "Failed send to Packet" << "\n";
			if (WSAGetLastError() == EPERM) {
				return GrantError = "������ �������� ����� �䱸";
			}
		}
		else {
			std::cout << "Send Success" << std::endl;
		}
		return "";
	}
	std::string ICMP::Receive(SOCKET sock) {
		
		int ipsize = sizeof(ipadd);
		//���Ź��� ��Ŷ�� �����Ϳ� ip�ּ� ����

		
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
	