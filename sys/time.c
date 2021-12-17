#include <sys/time.h>

#include <sys/get_syscall_id.h>

int sys_time_id = -1;

long long _time() {
	if (sys_time_id == -1) {
		sys_time_id = get_syscall_id("sys_time");
	}

	long long ret;
	__asm__ __volatile__ ("int $0x30" : "=b" (ret) : "a" (sys_time_id));

	return ret;
}
