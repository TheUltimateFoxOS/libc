#include <sys/net.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_dns_resolve_id = -1;

union ip_u dns_resolve(const char* domain, int nic_id) {
	if (sys_dns_resolve_id == -1) {
		sys_dns_resolve_id = get_syscall_id("sys_dns_resolve");
	}

	uint32_t ip = 0;

	__asm__ __volatile__ ("int $0x30" : "=b" (ip) : "a" (sys_dns_resolve_id), "b" (domain), "c" (nic_id));

	union ip_u ip_union;
	ip_union.ip = ip;

	return ip_union;
}