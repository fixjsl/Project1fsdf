#pragma once

class Traceroute
{
private:
	int ping1,ping2,ping3;
	
public:
	bool Init();
	void traceroute();
	int getPing();
	std::string getIP();
};

