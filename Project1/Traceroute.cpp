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
{	//에러메시지 배열 초기화
	ErrorMessage.clear();
	// 문자열을 ip구조체로 변환
	sockaddr_in destip;
	
	//핑 시작시간 저장
	int packetping[3];
	int i = 0; // 반복문 변수
	//멀티스레딩으로 패킷 3개보내기
	std::thread t1;
	packetping[0];
	std::thread t2;
	packetping[1];
	std::thread t3;
	packetping[2];
	//권한 오류 확인
	
	//receive
	while (true) {
		if (i == 3)  break;
		//패킷 수신
		std::string result = icmpPaket.Receive(sock);
		int endTime;
		//ping 계산 (endTime - startTime) if Timeout error = ping = 0;
		if (result != "") ping.push_back(0);
		else {
			
		}
		
		//에러메시지 저장
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





