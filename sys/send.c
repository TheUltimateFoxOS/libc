#include <sys/net.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_socket_send_id = -1;

int send(int socket, const void* data, size_t size) {
	if (sys_socket_send_id == -1) {
		sys_socket_send_id = get_syscall_id("sys_socket_send");
	}

	int success = 0;

	__asm__ __volatile__ ("int $0x30" : "=d" (success) : "a" (sys_socket_send_id), "b" (socket), "c" (data), "d" (size));


	return success;
}