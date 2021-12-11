#include <sys/close.h>

#include <sys/get_syscall_id.h>

int sys_close_id = -1;

void close(int fd) {
	if (sys_close_id == -1) {
		sys_close_id = get_syscall_id("sys_close");
	}
	__asm__ __volatile__ ("int $0x30" :: "a" (sys_close_id), "b" (fd));
}