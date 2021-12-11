#include <sys/memory.h>

#include <sys/get_syscall_id.h>

int sys_memory_alloc_id = -1;
int sys_memory_free_id = -1;

void* memory(void* ptr, size_t size, int mode) {

	switch (mode) {
		case MEM_ALLOC:
			{
				if (sys_memory_alloc_id == -1) {
					sys_memory_alloc_id = get_syscall_id("sys_memory_alloc");
				}

				void* memory_addr = NULL;
				__asm__ __volatile__ ("int $0x30" : "=b" (memory_addr) : "a" (sys_memory_alloc_id), "b" (size));
				return memory_addr;
			}
			break;
		
		case MEM_FREE:
			{
				if (sys_memory_free_id == -1) {
					sys_memory_free_id = get_syscall_id("sys_memory_free");
				}

				__asm__ __volatile__ ("int $0x30" : : "a" (sys_memory_free_id), "b" (size), "c" (ptr));
			}
			break;
		
		default:
			return NULL;
			break;
	}

	return NULL;
}