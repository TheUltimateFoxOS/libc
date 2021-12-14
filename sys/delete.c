#include <sys/delete.h>

#include <sys/get_syscall_id.h>

int sys_delete_id = -1;

void delete_(int fd) {
	if (sys_delete_id == -1) {
		sys_delete_id = get_syscall_id("sys_delete");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_delete_id), "b" (fd));
}