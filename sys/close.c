#include <sys/close.h>

void close(int fd) {
	__asm__ __volatile__ ("int $0x30" :: "a" (SYS_CLOSE), "b" (fd));
}