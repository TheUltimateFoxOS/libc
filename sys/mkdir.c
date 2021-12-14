#include <sys/mkdir.h>

#include <sys/get_syscall_id.h>

int sys_mkdir_id = -1;

void mkdir(const char* path) {
	if (sys_mkdir_id == -1) {
		sys_mkdir_id = get_syscall_id("sys_mkdir");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_mkdir_id), "b" (path));
}