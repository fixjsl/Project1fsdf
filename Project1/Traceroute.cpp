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
{	//�����޽��� �迭 �ʱ�ȭ
	ErrorMessage.clear();
	// ���ڿ��� ip����ü�� ��ȯ
	sockaddr_in destip;
	
	//�� ���۽ð� ����
	int packetping[3];
	int i = 0; // �ݺ��� ����
	//��Ƽ���������� ��Ŷ 3��������
	std::thread t1;
	packetping[0];
	std::thread t2;
	packetping[1];
	std::thread t3;
	packetping[2];
	//���� ���� Ȯ��
	
	//receive
	while (true) {
		if (i == 3)  break;
		//��Ŷ ����
		std::string result = icmpPaket.Receive(sock);
		int endTime;
		//ping ��� (endTime - startTime) if Timeout error = ping = 0;
		if (result != "") ping.push_back(0);
		else {
			
		}
		
		//�����޽��� ����
		ErrorMessage.push_back(result);
		i++;
	}
}

std::vector<int> Traceroute::getPing()
{
	return ping;
}



std::string Traceroute::getIP()
{
	return icmpPaket.getIp();
}

std::vector<std::string> Traceroute::getErrorMessage() {
	return ErrorMessage;
}





