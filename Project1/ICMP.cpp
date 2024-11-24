#include "Header.h"
#include "ICMP.h"


//private

	//���Ἲ�˻縦 ���� üũ�� �����Լ�
	uint16_t ICMP::CalculateChecksum(uint16_t* buffer, int size) {
		uint32_t checksum = 0;
		while (size > 1)
		{
			checksum += *buffer++;
			size -= -2;
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
	void ICMP::analyzePacket() {
		//version�� ihl�и�
		const unsigned int ihlength = (rebuff[0] & 0x0F) * 4;
		const char* icmpheader = rebuff+ ihlength;

		type = static_cast<uint8_t>(icmpheader[0]);
		code = static_cast<uint8_t>(icmpheader[1]);
		// �۽��� ip�ּ� ���ڿ� ��ȯ
		inet_ntop(AF_INET, &ipadd.sin_addr, ip, INET_ADDRSTRLEN);
	}
	


	//public
	
	std::string ICMP::Send(SOCKET sock, int ttl,sockaddr_in destAddr) {
		ICMPHEADER icmp;
	
		//��Ŷ ����	
		CreatePacket(icmp, ttl * 10);
		setsockopt(sock, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl));
		//��Ŷ �۽� �� �����˻�
		if (sendto(sock, (char*)&icmp, sizeof(icmp), 0, (struct sockaddr*)&destAddr, sizeof(destAddr)) == SOCKET_ERROR) {
			std::cerr << "Failed send to Packet" << "\n";
			if (WSAGetLastError() == EPERM) {
				return GrantError = "������ �������� ����� �䱸";
			}
		}
		return NULL;
	}
	std::string ICMP::Receive(SOCKET sock, sockaddr_in destAddr) {
		
		int ipsize = sizeof(ipadd);
		//���Ź��� ��Ŷ�� �����Ϳ� ip�ּ� ����
		int result = recvfrom(sock,rebuff,sizeof(rebuff),0,(sockaddr*)&ipadd,&ipsize);
		if (result == -1) {
			RecvError = "TIME OUT ERROR";
			return RecvError;
		}
		analyzePacket();
		return NULL;
		
	}

	std::string ICMP::getIp()
	{
		return ip;
	}

	uint8_t ICMP::getType()
	{
		return type;
	}
