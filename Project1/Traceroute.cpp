#include "Traceroute.h"
#include "ICMP.h"
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
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
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



