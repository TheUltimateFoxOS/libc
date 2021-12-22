#include <sys/write.h>
#include <sys/get_syscall_id.h>

int sys_write_id = -1;

void write(int fd, const void* buf, int count, int offset) {
	if (sys_write_id == -1) {
		sys_write_id = get_syscall_id("sys_write");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_write_id), "b" (fd), "c" (buf), "d" (count), "S" (offset));
}