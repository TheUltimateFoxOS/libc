#include <sys/env.h>
#include <stddef.h>

char** env(int mode) {
	char** env_ptr = NULL;
	__asm__ __volatile__ ("int $0x30" : "=c" (env_ptr) : "a" (SYS_ENV), "b" (mode));

	return env_ptr;
}

void env_set(int mode, void* data) {
	__asm__ __volatile__ ("int $0x30" : : "a" (SYS_ENV), "b" (mode), "c" (data));
}
