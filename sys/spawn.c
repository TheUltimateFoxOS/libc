#include <sys/spawn.h>

task* spawn(const char* path, const char* argv[], const char* envp[]) {
	task* t;
	__asm__ __volatile__ ("int $0x30" : "=a" (t) : "a" (SYS_SPAWN), "b"(path), "c"(argv), "d"(envp));
}