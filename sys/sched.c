#include <sys/sched.h>

void sched() {
	__asm__ __volatile__ ("int $0x30" :: "a" (SYS_SCHED));
}