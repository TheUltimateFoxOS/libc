#pragma once
#include <extern.h>
#include <stdint.h>

typedef uint64_t jmp_buf[8];

EXPOSEC void longjmp(jmp_buf state, int value);
EXPOSEC int setjmp(jmp_buf state);