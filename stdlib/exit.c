#include <stdlib.h>
#include <sys/exit.h>
#include <sys/write.h>
#include <stdio.h>
#include <buildin/thread.h>

shutdown_hook_t shutdown_hook[16] = { 0 };

void __libc_exit(int code) {
	if (shutdown_hook != NULL) {
		for (int i = 0; i < 16; i++) {
			if (shutdown_hook[i] != NULL) {
				shutdown_hook[i]();
			}
		}
	}

	//#warning "Deallocate allocated memory and stuff here!";

	__libc_kill_childs();
	__libc_uninit_stdio();
	__libc_uninit_alloc();

	// printf("Exit code %d\n", code);

	_exit(code);
}

void abort(void) {

	__libc_exit(EXIT_FAILURE);
}

void exit(int status) {
	__libc_exit(status);
}

void _Exit(int status) {
	__libc_exit(status);
}

void __libc_set_shutdown_hook(shutdown_hook_t hook) {
	for (int i = 0; i < 16; i++) {
		if (shutdown_hook[i] == NULL) {
			shutdown_hook[i] = hook;
			return;
		}
	}

	printf("--- WARNING --- No more space for shutdown hooks!\n");
}