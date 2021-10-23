#include <sys/seek_get.h>

int seek_get(int fd) {
	int seek;

	__asm__ __volatile__ ("int $0x30" : "=c" (seek) : "a" (SYS_SEEK_GET), "b" (fd));

	return seek;
}