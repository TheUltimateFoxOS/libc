#include <stdlib.h>
#include <sys/exit.h>
#include <stdio.h>

void __libc_exit(int code) {
	//#warning "Deallocate allocated memory and stuff here!";
	__libc_uninit_alloc();

	printf("Exit code %d\n", code);

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