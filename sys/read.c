#include <sys/read.h>

#include <stdbool.h>

void read(int fd, const void* buf, int count) {
	bool done = false;
	
	__asm__ __volatile__ ("mov %%rax, %%r8" : : "a" (&done));
	__asm__ __volatile__ ("int $0x30" : : "a" (SYS_READ), "b" (fd), "c" (buf), "d" (count));

	// this is done like that because we will process file io differently
	if(fd == STDIN) {
		while (!done) {
			__asm__ __volatile__ ("nop");
		}
	}
}