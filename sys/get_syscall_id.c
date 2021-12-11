#include <sys/get_syscall_id.h>

int get_syscall_id(char* name) {
	int sys_id = 0;
	__asm__ __volatile__("int $0x30" : "=a" (sys_id) : "a" (SYS_GET_SYSCALL_ID), "b" (name));

	return sys_id;
}
