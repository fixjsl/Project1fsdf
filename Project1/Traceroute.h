#pragma once
#include "Header.h"
class Traceroute
{
private:
	int ping[3] = {};
	SOCKET sock;
	ICMP icmpPaket;
public:
	bool Init();
	void traceroute(std::string destAddr,int ttl);
	int getPing1();
	int getPing2();
	int getPing3();
	std::string getIP();
};

