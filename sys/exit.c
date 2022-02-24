#include <sys/exit.h>

#include <sys/get_syscall_id.h>

int sys_exit_id = -1;

void _exit(int code) {
	if (sys_exit_id == -1) {
		sys_exit_id = get_syscall_id("sys_exit");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_exit_id), "b" (code));
}