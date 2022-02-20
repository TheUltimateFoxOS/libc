#include <sys/net.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_socket_disconnect_id = -1;

void disconnect(int socket) {
	if (sys_socket_disconnect_id == -1) {
		sys_socket_disconnect_id = get_syscall_id("sys_socket_disconnect");
	}


	__asm__ __volatile__ ("int $0x30" :: "a" (sys_socket_disconnect_id), "b" (socket));
}