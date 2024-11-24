#include "Traceroute.h"
#include "Header.h"

bool Traceroute::Init() {
	//소켓 초기화
	WSADATA win;
	if (WSAStartup(MAKEWORD(2, 2), &win) != 0) {
		std::cerr << "Failed Init" << "\n";
	}
	//타임아웃 시간 생성
	SYSTEMTIME st;
	st.wSecond = 5;
	//소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
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
