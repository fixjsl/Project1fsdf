#pragma once
class ICMP
{
private:
	//������ �ּ� ������ۿ� 
	char rebuff[1024]; // ���Ź��� ��Ŷ ������ ����
	sockaddr_in ipadd;// �۽��� ������� ip����
	char ICMPError[100];//��Ŷ ������ ����
	char RecvError[100];//���� �Լ� ����
	char ip[INET_ADDRSTRLEN];//ip���ڿ�
	uint8_t type;//��Ŷ Ÿ��
	uint8_t code;//��Ŷ �ڵ�



	//���Ἲ�˻縦 ���� üũ�� �����Լ�
	uint16_t CalculateChecksum(uint16_t* buffer, int size);
	// ��Ŷ�� ���� ��Ŷ ���� ��ȣ�� �޾� ��Ŷ�� �ʱ�ȭ �ϰ� ����
	void CreatePacket(ICMPHEADER& icmp, uint16_t crseq);
	//��Ŷ �м� �Լ�
	void analyzePacket();
	void ErrorCheck();
public:
	void Send(SOCKET sock, int ttl, sockaddr_in destAddr, int i);
	void Receive(SOCKET sock, sockaddr_in destAddr);
};

