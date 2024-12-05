#include "Header.h"
#include "ICMP.h"
#include "Traceroute.h"

void GrnadtICMP() {
	system("netsh advfirewall firewall add rule name=\"Allow ICMP\" protocol=icmpv4 dir=in action=allow");
}
int checkICMPGR(const std::string& ruleName) {
	std::string command = "powershell.exe Get-NetFirewallRule | Where-Object {$_.DisplayName -like '*" + ruleName + "*'}";
	int result = system(command.c_str());
	return result == 0;
}

int main() {
	if (!checkICMPGR("Allow ICMPv4-In")) {
		GrnadtICMP();
	}
	
	Traceroute tr;
	tr.Init();
	sockaddr_in destip = tr.Stadd("www.amazon.com");
	if ((int)&destip.sin_addr == 0) std::cout << "Error:: invailed url" << std::endl;
	for (int i = 1; i <= 30; i++)
	{
		if (tr.traceroute(destip, i) == true) {
			break;
		}

	}
	
	return 0;
}