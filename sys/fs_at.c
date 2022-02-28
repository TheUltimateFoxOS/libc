#include <sys/fs_at.h>

#include <sys/get_syscall_id.h>
#include <string.h>

int sys_fs_at_id = -1;

bool fs_at(int idx, char* out) {
	if (sys_fs_at_id == -1) {
		sys_fs_at_id = get_syscall_id("sys_fs_at");
	}

	bool success = false;

	__asm__ __volatile__ ("int $0x30" : "=a" (success) : "a" (sys_fs_at_id), "b" (out), "c" (idx));

	return success;
}