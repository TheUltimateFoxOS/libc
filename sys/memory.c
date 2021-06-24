#include <sys/memory.h>

void* memory(void* ptr, size_t size, int mode) {
	void* memory_addr = NULL;
	__asm__ __volatile__ ("int $0x30" : "=c" (memory_addr) : "a" (SYS_MEMORY), "b" (mode), "c" (ptr), "d" (size));

	return memory_addr;
}