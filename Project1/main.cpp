#include "Header.h"
#include "ICMP.h"
#include "Traceroute.h"

int main() {
	
	Traceroute tr;
	tr.Init();
	tr.traceroute("8.8.8.8", 30);
	return 0;
}