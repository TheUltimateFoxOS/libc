#include <sys/net.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_socket_connect_id = -1;

int connect(uint32_t ip, uint16_t port, int socket_type) {
	if (sys_socket_connect_id == -1) {
		sys_socket_connect_id = get_syscall_id("sys_socket_connect");
	}

	int socket_id = 0;

	__asm__ __volatile__ ("int $0x30" : "=d" (socket_id) : "a" (sys_socket_connect_id), "b" (socket_type), "c" (ip), "d" (port));


	return socket_id;
}