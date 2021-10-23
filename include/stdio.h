#pragma once
#include <extern.h>
#include <stdarg.h>
#include <stddef.h>

#include <sys/seek_set.h> // for SEEK_* definitions

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
EXPOSEC char getchar();

#define FILE_BUFFER_SIZE 512

typedef struct file_t {
	int inner_fd;
    int is_readable;
    int is_writable;
    int is_eof;
    int is_error;
    size_t buffer_i;
    char buffer[FILE_BUFFER_SIZE];
} FILE;

EXPOSEC int fclose(FILE* stream);
EXPOSEC int fflush(FILE *stream);
EXPOSEC FILE *fopen(const char *filename, const char *mode);
EXPOSEC size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
EXPOSEC int fseek(FILE *stream, long offset, int whence);
EXPOSEC long ftell(FILE *stream);
EXPOSEC size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);