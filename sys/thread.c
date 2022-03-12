#include <sys/thread.h>

#include <sys/get_syscall_id.h>

int sys_thread_id = -1;

task_t* thread(void* entry, bool clone_cwd) {
	if (sys_thread_id == -1) {
		sys_thread_id = get_syscall_id("sys_thread");
	}

	task_t* task;
	__asm__ __volatile__ ("int $0x30" : "=a" (task) : "a" (sys_thread_id), "b" (entry), "c" (clone_cwd));

	return task;
}