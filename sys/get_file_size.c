#include <sys/get_file_size.h>

#include <sys/get_syscall_id.h>

int sys_get_file_size_id = -1;

size_t get_file_size(int fd) {
	if (sys_get_file_size_id == -1) {
		sys_get_file_size_id = get_syscall_id("sys_get_file_size");
	}

	size_t size = 0;
	__asm__ __volatile__ ("int $0x30" : "=a" (size) : "a" (sys_get_file_size_id), "b" (fd));

	return size;
}
