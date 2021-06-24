#pragma once
#include <extern.h>
#include <stddef.h>

#define SYS_MEMORY 4

#define MEM_ALLOC 0
#define MEM_FREE 1

EXPOSEC void* memory(void* ptr, size_t size, int mode);