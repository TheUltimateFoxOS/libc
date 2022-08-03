#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


int _scanf_read(char* out) {
	int idx = 0;
	char c;
	while ((c = getchar()) != ' ' && c != '\n') {
		out[idx] = c;
		idx++;
	}
	out[idx] = '\0';
	return idx;
}

int scanf(const char* format, ...) {
	va_list vl;
	va_start(vl, format);
	int idx = 0;

	char buffer[256] = { 0 };

	while(*format) {
		if(*format == '%') {
			format++;
			switch(*format) {
				case 's':
					{
						memset(buffer, 0, 256);
						idx += _scanf_read(buffer);
						char* str = va_arg(vl, char*);
						strcpy(str, buffer);
					}
					break;
				case 'c':
					{
						char c = getchar();
						idx++;
						char* ch = va_arg(vl, char*);
						*ch = c;
					}
					break;
				case 'd':
				case 'u':
					{
						memset(buffer, 0, 256);
						idx += _scanf_read(buffer);
						long number = strtol(buffer, NULL, 10);
						long* num = va_arg(vl, long*);
						*num = number;
					}
					break;
				case 'x':
				case 'p':
					{
						memset(buffer, 0, 256);
						idx += _scanf_read(buffer);
						long number = strtol(buffer, NULL, 16);
						long* num = va_arg(vl, long*);
						*num = number;
					}
					break;
				default:
					printf("Unknown format specifier: %c\n", *format);
					abort();
					break;
			}
		}

		format++;
	}

out:
	return idx;
}