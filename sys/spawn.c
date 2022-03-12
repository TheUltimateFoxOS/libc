#include <sys/spawn.h>

#include <sys/get_syscall_id.h>

int sys_spawn_id = -1;

task_t* spawn(const char* path, const char* argv[], const char* envp[], bool clone_cwd) {
	if (sys_spawn_id == -1) {
		sys_spawn_id = get_syscall_id("sys_spawn");
	}

	task_t* task;
	__asm__ __volatile__ ("int $0x30" : "=a" (task) : "a" (sys_spawn_id), "b" (path), "c" (argv), "d" (envp), "S" (clone_cwd));

	return task;
}