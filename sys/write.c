#include <sys/write.h>

void write(int fd, const void* buf, int count) {
	__asm__ __volatile__ ("int $0x30" : : "a" (SYS_WRITE), "b" (fd), "c" (buf), "d" (count));
}