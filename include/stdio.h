#pragma once
#include <extern.h>
#include <stdarg.h>

#define ZEROPAD	1
#define SIGN	2
#define PLUS	4
#define SPACE	8
#define LEFT	16
#define SMALL	32
#define SPECIAL	64

EXPOSEC int vsprintf(char *buf, const char *fmt, va_list args);
EXPOSEC int printf(const char *fmt, ...);
EXPOSEC int sprintf(char *buf, const char *fmt, ...);