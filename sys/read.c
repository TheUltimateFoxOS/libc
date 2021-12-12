#include <sys/read.h>
#include <sys/get_syscall_id.h>

#include <errno.h>

int sys_read_id = -1;

void read(int fd, const void* buf, int count, int offset) {
	if (sys_read_id == -1) {
		sys_read_id = get_syscall_id("sys_read");
	}

	int error;

	__asm__ __volatile__ ("int $0x30" : "=a" (error) : "a" (sys_read_id), "b" (fd), "c" (buf), "d" (count), "S" (offset));

	if (error != 0) {
		errno = error;
	}
}