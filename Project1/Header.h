#pragma once
#include <cstdio>
#include <cstring> 
#include <cstdint>
#include <chrono> 
#include <thread>
#include <cstring>


#if defined(_WIN32) || defined(_WIN64)

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "ws2_32.lib")



#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

#endif
