#include <sys/net.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_icmp_echo_reqest_id = -1;

bool icmp_echo_request(uint32_t ip, int nic_id) {
	if (sys_icmp_echo_reqest_id == -1) {
		sys_icmp_echo_reqest_id = get_syscall_id("sys_icmp_echo_request");
	}

	bool got_response = false;

	__asm__ __volatile__ ("int $0x30" : "=b" (got_response) : "a" (sys_icmp_echo_reqest_id), "b" (ip), "c" (nic_id));


	return got_response;
}