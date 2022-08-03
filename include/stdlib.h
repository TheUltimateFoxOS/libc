#pragma once

#include <extern.h>
#include <stddef.h>
#include <stdbool.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define START_MARKER 0xdeadbeef

typedef void (*shutdown_hook_t)(void);

EXPOSEC void abort(void);
EXPOSEC void exit(int status);
EXPOSEC void _Exit(int status);

EXPOSEC void __libc_exit(int code);

EXPOSEC void* __libc_malloc(size_t size);
EXPOSEC void __libc_free(void* address, size_t size);
EXPOSEC void __libc_init_alloc();
EXPOSEC void __libc_uninit_alloc();
EXPOSEC void __libc_set_shutdown_hook(shutdown_hook_t hook);

EXPOSEC void* malloc(size_t size);
EXPOSEC void free(void* addr);
EXPOSEC void* calloc(size_t count, size_t size);
EXPOSEC void* realloc(void* pointer, size_t size);

EXPOSEC char* getenv(const char* name);

EXPOSEC bool resolve_check(char* path, char* output, bool check_child);
EXPOSEC bool resolve(char* path, char* output);

EXPOSEC void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));
EXPOSEC int atoi(const char *str);

EXPOSEC void system(char* command);

EXPOSEC long strtol(char* input, char** out, int number_system_base);
EXPOSEC int scanf(const char* format, ...);