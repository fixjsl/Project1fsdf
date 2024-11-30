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
	int timeout = 5000;
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
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
		std::cout << "Sucess create Socket" << "\n";
		return true;
	}
	
}

sockaddr_in Traceroute::Stadd(std::string destAddr)
{
	sockaddr_in destip;
	memset(&destip, 0, sizeof(destip));
	destip.sin_family = AF_INET;
	// ���ڿ��� ip�� �ƴ� �������� ��� �������ּҸ� ip�� ��ȯ ip�� ��� ���ڿ��� ip������ ��ȯ�ϰ� ����
	if (inet_pton(AF_INET, destAddr.c_str(), &destip.sin_addr) != 1) {
		struct addrinfo hint, * result;
		memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_RAW;
		

		int red = getaddrinfo(destAddr.c_str(), NULL, &hint, &result);
		if (red != 0) {
			ErrorMessage.push_back("invalid domain");
			return destip;// �� ip����
		}
		destip = *(sockaddr_in*)result->ai_addr;
		freeaddrinfo(result);
	}
	return destip;
}

bool Traceroute::traceroute(sockaddr_in destAddr, int ttl)
{	//�����޽��� �迭 �ʱ�ȭ
	ErrorMessage.clear();
	//���� ttl����
	if (setsockopt(sock, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl)) < 0) {
		std::cout << "Failed set ttl : " << WSAGetLastError() << std::endl;
	}
	else std::cout << "Success set ttl" << std::endl;
	
	
	
	//�� ���۽ð� ����
	
	// ��Ŷ 3��������
	for (int i = 0; i < 3; i++) {
	icmpPaket.Send(sock, ttl+i, destAddr);
	//�۽� ���۽ð�
	DWORD start = timeGetTime();
	//���Ÿ��
	std::string Rresult = icmpPaket.Receive(sock);
	//Ÿ�Ӿƿ� Ȯ��
	if (Rresult != "") {
		ErrorMessage.push_back("Access Failed");
		ping.push_back(0);
	}
	else {
		DWORD end = timeGetTime();
		DWORD dur = end - start;
		ping.push_back(dur);
	}
	// ������ Ȯ��
	if ((int)icmpPaket.getType() == 0) {
		return true;
	}
	else return false;
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

std::string Traceroute::getErrorMessage(int i) {
	return ErrorMessage[i];
}





