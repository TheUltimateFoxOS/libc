#pragma once
#include <extern.h>
#include <stdint.h>
#include <stddef.h>

#define FAST_MEM

EXPOSEC char* strcpy(char* dest, const char* src);
EXPOSEC int strlen(char* src);
EXPOSEC size_t strnlen(const char *s, size_t maxlen);
EXPOSEC char* strcat(char* dest, const char* src);
EXPOSEC int strcmp(char* str1, char* str2);
EXPOSEC const char* strstr(const char* X, const char* Y);
EXPOSEC char* strchr(const char* s, int c);
EXPOSEC char* strrchr(const char* s, int c);
EXPOSEC int strncmp(const char* s1, const char* s2, size_t n );
EXPOSEC char* strncpy(char* _dst, const char* _src, size_t count);

EXPOSEC void* memcpy(void* dest, const void* src, size_t n);
EXPOSEC void* memset(void* start, uint8_t value, uint64_t num);
EXPOSEC int memcmp(const void * _s1, const void* _s2, size_t n);
