#pragma once
#include "Header.h"
#include "ICMP.h"
class Traceroute
{
private:
	std::vector<int> ping; // ping ����
	SOCKET sock; // ����
	ICMP icmpPaket; // ��Ŷ
	std::vector<std::string> ErrorMessage;// �����޼���
public:
	bool Init(); // ���� �ʱ�ȭ
	void traceroute(std::string destAddr,int ttl);// traceroute�Լ� (�ڵ忡�� ���� �ݺ����� ����Ͽ� ���)
	std::vector<int> getPing(); //ping�� ��ȯ�ϴ� �Լ�
	std::string getIP(); // ip�� ��ȯ�ϴ� �Լ�
	std::vector<std::string> getErrorMessage(); // �����޽����� ��ȯ�ϴ� �Լ� 0~2���� ���� �־������
};

