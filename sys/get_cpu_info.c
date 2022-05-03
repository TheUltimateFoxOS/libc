#include <sys/get_cpu_info.h>
#include <sys/get_syscall_id.h>

int sys_get_cpu_info_id = -1;

int get_cpu_info(cpu_info_t* cpu_info) {
	if (sys_get_cpu_info_id == -1) {
		sys_get_cpu_info_id = get_syscall_id("sys_get_cpu_info");
	}

	int size = 0;
	__asm__ __volatile__ ("int $0x30" : "=c" (size) : "a" (sys_get_cpu_info_id), "b" (cpu_info));

	return size;
}