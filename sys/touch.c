#include <sys/mkdir.h>

#include <sys/get_syscall_id.h>

int sys_touch_id = -1;

void touch(const char* path) {
	if (sys_touch_id == -1) {
		sys_touch_id = get_syscall_id("sys_touch");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_touch_id), "b" (path));
}