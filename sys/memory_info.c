#include <sys/memory_info.h>

#include <sys/get_syscall_id.h>

int sys_memory_info_id = -1;

memory_info_t memory_info() {
	if (sys_memory_info_id == -1) {
		sys_memory_info_id = get_syscall_id("sys_memory_info");
	}

	memory_info_t info;
	__asm__ __volatile__ ("int $0x30" : "=a" (info.total), "=b" (info.free), "=c" (info.used), "=d" (info.reserved) : "a" (sys_memory_info_id));

	return info;
}
