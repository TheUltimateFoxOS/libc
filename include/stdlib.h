#pragma once
#include <extern.h>
#include <stddef.h>


#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define START_MARKER 0xdeadbeef

EXPOSEC void abort(void);
EXPOSEC void exit(int status);
EXPOSEC void _Exit(int status);

EXPOSEC void __libc_exit(int code);

EXPOSEC void* __libc_malloc(size_t size);
EXPOSEC void __libc_free(void* address);
EXPOSEC void __libc_init_alloc();
EXPOSEC void __libc_uninit_alloc();

EXPOSEC void* malloc(size_t size);
EXPOSEC void free(void* addr);
EXPOSEC void* calloc(size_t count, size_t size);
EXPOSEC void* realloc(void* pointer, size_t size);