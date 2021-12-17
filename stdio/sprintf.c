#include <stdio.h>

int sprintf(char *buf, const char *fmt, ...) {
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsprintf(buf, fmt, args);
	va_end(args);
	return i;
}

int snprintf(char *buf, size_t size, const char *fmt, ...) {
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsnprintf(buf, size, fmt, args);
	va_end(args);
	return i;
}