#include <sys/open.h>

#include <sys/get_syscall_id.h>

int sys_open_id = -1;

int open(const char* path) {
	if (sys_open_id < 0) {
		sys_open_id = get_syscall_id("sys_open");
	}

	int fd = -1;
	__asm__ __volatile__ ("int $0x30" : "=d" (fd) : "a" (sys_open_id), "b" (path));

	return fd;
}