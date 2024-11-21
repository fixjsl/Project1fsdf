#include "Header.h"
//IPHEADER 구조체 정의
struct iphdr {
	uint8_t ihl : 4;       
	uint8_t version : 4;    
	uint8_t tos;            
	uint16_t tot_len;       
	uint16_t id;           // id
	uint16_t frag_off;      
	uint8_t ttl;           // TTL
	uint8_t protocol;      // 프로토콜
	uint16_t check;        // 체크섬
	uint32_t saddr;        // 출발 주소
	uint32_t daddr;        // 도착 주소
};
//ICMPHEADER구조체 정의
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
	//무결성검사를 위한 체크섬 생성함수
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
	// 패킷과 현재 패킷 생성 번호를 받아 패킷을 초기화 하고 리턴
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
	//수신받은 라우터의 ip와 핑을 출력
	std::string printIpAp(struct iphdr* ipheader) {
		char ip[INET_ADDRSTRLEN];
		struct in_addr srcip;
		srcip.s_addr = ipheader->saddr;
		inet_ntop(AF_INET, &srcip.s_addr, ip, INET_ADDRSTRLEN);
		return ip
	}
	void Send(SOCKET sock, int ttl,sockaddr_in destAddr,int i) {
		ICMPHEADER icmp;
		//패킷무결성을 위한 시스템시간 현재 초 가져오기
		int sysse = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 10;
		CreatePacket(icmp, ttl * 10+sysse);
		setsockopt(sock, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl));
		//패킷 송신 및 오류검사
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