#include <stdlib.h>
#include <sys/resolve_symbol.h>
#include <stdio.h>

void __libc_exit(int code) {
	//#warning "Deallocate allocated memory and stuff here!";
	__libc_uninit_alloc();

	void* exit_func = resolve_symbol("task_entry.exit");

	printf("Exit code %d\n", code);

	__asm__ __volatile__ ("jmp %%rax" : : "a" (exit_func));
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