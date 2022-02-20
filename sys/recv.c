#include <sys/net.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_socket_recv_id = -1;

int recv(int socket, void* data, size_t size) {
	if (sys_socket_recv_id == -1) {
		sys_socket_recv_id = get_syscall_id("sys_socket_recv");
	}

	int num_bytes = 0;

	__asm__ __volatile__ ("int $0x30" : "=d" (num_bytes) : "a" (sys_socket_recv_id), "b" (socket), "c" (data), "d" (size));


	return num_bytes;
}