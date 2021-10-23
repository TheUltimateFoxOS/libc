#include <sys/seek_set.h>

void seek_set(int fd, int offset, int mode) {
	__asm__ __volatile__ ("int $0x30" :: "a"(SYS_SEEK_SET), "b"(fd), "c"(offset), "d"(mode));
}