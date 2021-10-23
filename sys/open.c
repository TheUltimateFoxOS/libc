#include <sys/open.h>

int open(const char* path, const char* mode) {
	int fd = -1;
	__asm__ __volatile__ ("int $0x30" : "=d" (fd) : "a" (SYS_OPEN), "b" (path), "c" (mode));

	return fd;
}