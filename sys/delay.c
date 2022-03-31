#include <sys/delay.h>
#include <sys/get_syscall_id.h>

int sys_delay_id = -1;

void delay(int ms) {
	if (sys_delay_id == -1) {
		sys_delay_id = get_syscall_id("sys_delay");
	}

	__asm__ __volatile__ ("int $0x30" :: "a" (sys_delay_id), "b" (ms));
}
