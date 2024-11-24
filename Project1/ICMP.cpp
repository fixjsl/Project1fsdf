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
	//도착지 주소 저장버퍼와 
	char rebuff[1024]; // 수신받은 패킷 데이터 저장
	sockaddr_in ipadd;// 송신한 라우터의 ip저장
	char ICMPError[100];//패킷 데이터 에러
	char RecvError[100];//수신 함수 에러
	char ip[INET_ADDRSTRLEN];//ip문자열
	uint8_t type;//패킷 타입
	uint8_t code;//패킷 코드



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
	//패킷 분석 함수
	void analyzePacket() {
		//version과 ihl분리
		const unsigned int ihlength = (rebuff[0] & 0x0F) * 4;
		const char* icmpheader = rebuff+ ihlength;

		type = static_cast<uint8_t>(icmpheader[0]);
		code = static_cast<uint8_t>(icmpheader[1]);
		// 송신한 ip주소 문자열 변환
		inet_ntop(AF_INET, &ipadd.sin_addr, ip, INET_ADDRSTRLEN);
	}
	void ErrorCheck() {
		int errcode = WSAGetLastError();
		switch (errcode)
		{
		default:
			break;
		}

		}
public:	
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
	void Receive(SOCKET sock, sockaddr_in destAddr) {
		
		int ipsize = sizeof(ipadd);
		//수신받은 패킷의 데이터와 ip주소 저장
		int result = recvfrom(sock,rebuff,sizeof(rebuff),0,(sockaddr*)&ipadd,&ipsize);
		analyzePacket();
		
	}
};

void INITWAS() {
	WSADATA win;
	if (WSAStartup(MAKEWORD(2, 2), &win) != 0) {
		std::cerr << "Failed Init" << "\n";
	}
}
bool CreateSocket() {
	SYSTEMTIME st;
	st.wSecond = 5;
	//소켓 생성
	SOCKET sock =  socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	//소켓 오류 설정
	if (sock == INVALID_SOCKET) {
		std::cerr << "Failed Socket create" << "\n";
		std::cerr << "Error : " << WSAGetLastError() << "\n";
		return false;
	}
	else {
		// 타임아웃 시간 설정
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&st.wSecond, sizeof(st.wSecond));
		std::cout << "Sucess create Socket" << "\n";
		return true;
	}
}


void Traceroute() {
	int ping[3];


}