#pragma once
#include "Header.h"
class ICMP
{
private:
	//������ �ּ� ������ۿ� 
	char rebuff[1024]; // ���Ź��� ��Ŷ ������ ����
	sockaddr_in ipadd;// �۽��� ������� ip����
	std::string ICMPError;//��Ŷ ������ ����
	std::string GrantError;
	std::string RecvError;//���� �Լ� ����
	char ip[INET_ADDRSTRLEN] = "";//ip���ڿ�
	uint8_t type = NULL;//��Ŷ Ÿ��
	uint8_t code = NULL;//��Ŷ �ڵ�



	//���Ἲ�˻縦 ���� üũ�� �����Լ�
	uint16_t CalculateChecksum(uint16_t* buffer, int size);
	// ��Ŷ�� ���� ��Ŷ ���� ��ȣ�� �޾� ��Ŷ�� �ʱ�ȭ �ϰ� ����
	void CreatePacket(ICMPHEADER& icmp, uint16_t crseq);
	//��Ŷ �м� �Լ�
	
	//String to ip
	sockaddr_in Stadd(std::string destAddr);
public:
	
	std::string Send(SOCKET sock, int ttl, std::string destAddr);
	std::string Receive(SOCKET sock);
	std::string getIp();
	uint8_t getType();
};

