#include <stdlib.h>
#include <sys/exit.h>
#include <sys/write.h>
#include <stdio.h>

shutdown_hook_t shutdown_hook;

void __libc_exit(int code) {
	if (shutdown_hook != NULL) {
		shutdown_hook();
	}

	//#warning "Deallocate allocated memory and stuff here!";
	__libc_uninit_alloc();

	// printf("Exit code %d\n", code);

	_exit();
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
	if (shutdown_hook != NULL) {
		write(STDERR, "--- WARNING: shutdown hook already set! overwriting! ---\n", 58, 0);
	}
	shutdown_hook = hook;
}