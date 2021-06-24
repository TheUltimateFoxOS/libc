#include <stdio.h>
#include <stddef.h>
#include <sys/write.h>

int printf(const char *fmt, ...) {
	char printf_buf[1024 * 4];
	va_list args;
	int printed;

	va_start(args, fmt);
	printed = vsprintf(printf_buf, fmt, args);
	va_end(args);

	write(STDOUT, printf_buf, printed);

	return printed;
}