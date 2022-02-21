#include <sys/env.h>
#include <stddef.h>

#include <sys/get_syscall_id.h>

int sys_env_id = -1;

char** env(int mode) {
	if (sys_env_id == -1) {
		sys_env_id = get_syscall_id("sys_env");
	}

	char** env_ptr = NULL;
	__asm__ __volatile__ ("int $0x30" : "=c" (env_ptr) : "a" (sys_env_id), "b" (mode));

	return env_ptr;
}

void env2(int mode) {
	if (sys_env_id == -1) {
		sys_env_id = get_syscall_id("sys_env");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_env_id), "b" (mode));
}

void env_set(int mode, void* data) {
	if (sys_env_id == -1) {
		sys_env_id = get_syscall_id("sys_env");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_env_id), "b" (mode), "c" (data));
}

void env_set2(int mode, int data, void* data2) {
	if (sys_env_id == -1) {
		sys_env_id = get_syscall_id("sys_env");
	}

	__asm__ __volatile__ ("int $0x30" : : "a" (sys_env_id), "b" (mode), "c" (data), "d" (data2));
}

// void env_set3(int mode, int data) {
// 	if (sys_env_id == -1) {
// 		sys_env_id = get_syscall_id("sys_env");
// 	}

// 	__asm__ __volatile__ ("int $0x30" : : "a" (sys_env_id), "b" (mode), "c" (data));
// }