#include <sys/env.h>
#include <stddef.h>

char** env(int mode) {
	char** env_ptr = NULL;
	__asm__ __volatile__ ("int $0x30" : "=c" (env_ptr) : "a" (SYS_ENV), "b" (mode));

	return env_ptr;
}

void env2(int mode) {
	__asm__ __volatile__ ("int $0x30" : : "a" (SYS_ENV), "b" (mode));
}

void env_set(int mode, void* data) {
	__asm__ __volatile__ ("int $0x30" : : "a" (SYS_ENV), "b" (mode), "c" (data));
}

void env_set2(int mode, int data, void* data2) {
	__asm__ __volatile__ ("int $0x30" : : "a" (SYS_ENV), "b" (mode), "c" (data), "d" (data2));
}

void env_set3(int mode, int data) {
	__asm__ __volatile__ ("int $0x30" : : "a" (SYS_ENV), "b" (mode), "c" (data));
}