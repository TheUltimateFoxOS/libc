#include <sys/dir_at.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_dir_at_id = -1;

dir_t dir_at(int idx, const char* path) {
	if (sys_dir_at_id == -1) {
		sys_dir_at_id = get_syscall_id("sys_dir_at");
	}

	dir_t dir;
	memset(&dir, 0, sizeof(dir));

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_dir_at_id), "b" (path), "c" (idx), "d" (&dir));

	return dir;
}