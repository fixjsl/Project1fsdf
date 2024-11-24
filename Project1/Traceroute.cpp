#include "Traceroute.h"
#include "ICMP.h"
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
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
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

void Traceroute::traceroute(std::string destAddr, int ttl)
{
}

int Traceroute::getPing1()
{
	return ping[0];
}

int Traceroute::getPing2()
{
	return ping[1];
}

std::string Traceroute::getIP()
{
	return icmpPaket.getIp();
}

int Traceroute::getPing3()
{
	return ping[2];
}



