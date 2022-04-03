#include <sys/delete_dir.h>
#include <sys/get_syscall_id.h>

int sys_delete_dir_id = -1;

void delete_dir(char* path) {
	if (sys_delete_dir_id == -1) {
		sys_delete_dir_id = get_syscall_id("sys_delete_dir");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_delete_dir_id), "b" (path));
}