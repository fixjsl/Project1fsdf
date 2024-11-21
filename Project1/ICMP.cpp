#include "Header.h"
//IPHEADER ����ü ����
struct iphdr {
	uint8_t ihl : 4;       
	uint8_t version : 4;    
	uint8_t tos;            
	uint16_t tot_len;       
	uint16_t id;           // id
	uint16_t frag_off;      
	uint8_t ttl;           // TTL
	uint8_t protocol;      // ��������
	uint16_t check;        // üũ��
	uint32_t saddr;        // ��� �ּ�
	uint32_t daddr;        // ���� �ּ�
};
//ICMPHEADER����ü ����
struct ICMPHEADER
{
	uint8_t Type;
	uint8_t Code;
	uint16_t Checksum;
	uint16_t id;
	uint16_t sequence;
};

class ICMPRERV {
private:
	//���Ἲ�˻縦 ���� üũ�� �����Լ�
	uint16_t CalculateChecksum(uint16_t* buffer, int size) {
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
	void CreatePacket(ICMPHEADER& icmp, uint16_t crseq) {
		memset(&icmp, 0, sizeof(ICMPHEADER));
		icmp.Type = 8;
		icmp.Code = 0;
		icmp.id = (uint16_t)GetCurrentProcessId();
		icmp.sequence = crseq;
		icmp.Checksum = 0;
		icmp.Checksum = CalculateChecksum((uint16_t*)&icmp, sizeof(icmp));
	}
public:
	//���Ź��� ������� ip�� ���� ���
	std::string printIpAp(struct iphdr* ipheader) {
		char ip[INET_ADDRSTRLEN];
		struct in_addr srcip;
		srcip.s_addr = ipheader->saddr;
		inet_ntop(AF_INET, &srcip.s_addr, ip, INET_ADDRSTRLEN);
		return ip
	}
	void Send(SOCKET sock, int ttl,sockaddr_in destAddr,int i) {
		ICMPHEADER icmp;
		//��Ŷ���Ἲ�� ���� �ý��۽ð� ���� �� ��������
		int sysse = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 10;
		CreatePacket(icmp, ttl * 10+sysse);
		setsockopt(sock, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl));
		//��Ŷ �۽� �� �����˻�
		if (sendto(sock, (char*)&icmp, sizeof(icmp), 0, (struct sockaddr*)&destAddr, sizeof(destAddr)) == SOCKET_ERROR) {
			std::cerr << "Failed send to Packet" << "\n";
		}
	}
	void Receive() {
		char reipbuff[1024];
		sockaddr_in ipadd;
		recvfrom()
	}
};

void INITWAS() {
	WSADATA win;
	if (WSAStartup(MAKEWORD(2, 2), &win) != 0) {
		str::cerr << "Failed Init" << "\n";
	}
}
bool CreateSocket() {
	SOCKET sock =  socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Failed Socket create" << "\n";
		std::cerr << "Error : " << WSAGetLastError() << "\n";
		return false;
	}
	else {
		std::cout << "Sucess create Socket" << "\n";
		return true;
	}

	
}


void traceroute() {
	


}