#pragma once
#include <extern.h>
#include <stdarg.h>
#include <stddef.h>

#define BUFSIZ 1024

#define ZEROPAD	1
#define SIGN	2
#define PLUS	4
#define SPACE	8
#define LEFT	16
#define SMALL	32
#define SPECIAL	64

EXPOSEC int vsprintf(char *buf, const char *fmt, va_list args);
EXPOSEC int vsnprintf(char *buf, size_t size, const char *fmt, va_list args);
EXPOSEC int printf(const char *fmt, ...);
EXPOSEC int sprintf(char *buf, const char *fmt, ...);
EXPOSEC int snprintf(char *buf, size_t size, const char *fmt, ...);
EXPOSEC char getchar();
EXPOSEC char putchar(char c);
EXPOSEC int gets(char* buffer);

#define FILE_BUFFER_SIZE 512

typedef struct file_t {
	int inner_fd;
	int size;
	int pos;
} FILE;

enum SEEK_WHENCE {
	SEEK_SET,
	SEEK_CUR,
	SEEK_END
};

extern struct file_t* stdout;
extern struct file_t* stdin;
extern struct file_t* stderr;

#define EOF (-1)

EXPOSEC int fclose(FILE* stream);
EXPOSEC int fflush(FILE *stream);
EXPOSEC FILE *fopen(const char *filename, const char *mode);
EXPOSEC FILE *freopen(const char *filename, const char *mode, FILE *stream);
EXPOSEC size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
EXPOSEC int fseek(FILE *stream, long offset, int whence);
EXPOSEC long ftell(FILE *stream);
EXPOSEC size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
EXPOSEC int fprintf(FILE *stream, const char *format, ...);
EXPOSEC int fputs(const char *s, FILE *stream);
EXPOSEC int fputc(int c, FILE *stream);
EXPOSEC int fgetc(FILE *stream);
EXPOSEC char *fgets(char *s, int size, FILE *stream);
EXPOSEC int ferror(FILE *stream);
EXPOSEC void clearerr(FILE *stream);
EXPOSEC int feof(FILE* stream);

EXPOSEC int getc(FILE *stream);
EXPOSEC int ungetc(int c, FILE *stream);

EXPOSEC int remove(const char *filename);
EXPOSEC void rewind(FILE *stream);

EXPOSEC void __libc_init_stdio();
EXPOSEC void __libc_uninit_stdio();