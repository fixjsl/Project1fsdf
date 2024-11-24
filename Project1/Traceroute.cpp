#include "Traceroute.h"
#include "Header.h"

bool Traceroute::Init() {
	//���� �ʱ�ȭ
	WSADATA win;
	if (WSAStartup(MAKEWORD(2, 2), &win) != 0) {
		std::cerr << "Failed Init" << "\n";
	}
	//Ÿ�Ӿƿ� �ð� ����
	SYSTEMTIME st;
	st.wSecond = 5;
	//���� ����
	SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	//���� ���� ����
	if (sock == INVALID_SOCKET) {
		std::cerr << "Failed Socket create" << "\n";
		std::cerr << "Error : " << WSAGetLastError() << "\n";
		return false;
	}
	else {
		// Ÿ�Ӿƿ� �ð� ����
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&st.wSecond, sizeof(st.wSecond));
		std::cout << "Sucess create Socket" << "\n";
		return true;
	}
}
