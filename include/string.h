#pragma once
#include <extern.h>
#include <stdint.h>
#include <stddef.h>

#define FAST_MEM

EXPOSEC char* strcpy(char* dest, const char* src);
EXPOSEC int strlen(const char* src);
EXPOSEC size_t strnlen(const char *s, size_t maxlen);
EXPOSEC char* strcat(char* dest, const char* src);
EXPOSEC int strcmp(const char* str1, const char* str2);
EXPOSEC const char* strstr(const char* X, const char* Y);
EXPOSEC char* strchr(const char* s, int c);
EXPOSEC char* strrchr(const char* s, int c);
EXPOSEC int strncmp(const char* s1, const char* s2, size_t n );
EXPOSEC char* strncpy(char* _dst, const char* _src, size_t count);
EXPOSEC char* strtok(char* src_string, char* delim);
EXPOSEC size_t strspn(const char* str1, const char* str2);
EXPOSEC size_t strcspn(const char* str1, const char* str2);

EXPOSEC void* memcpy(void* dest, const void* src, size_t n);
EXPOSEC void* memmove(void* dest, const void* src, size_t len);
EXPOSEC void* memset(void* start, uint8_t value, uint64_t num);
EXPOSEC int memcmp(const void * _s1, const void* _s2, size_t n);

EXPOSEC void* memset16(void* start, uint16_t value, uint64_t num);
EXPOSEC void* memset32(void* start, uint32_t value, uint64_t num);
EXPOSEC void* memset64(void* start, uint64_t value, uint64_t num);