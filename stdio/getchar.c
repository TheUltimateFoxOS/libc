#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/read.h>
#include <sys/write.h>

char getchar() {

	errno = 0;

	char input[1];
	read(STDIN, input, 1, 0);

	return input[0];
}

char putchar(char c) {

	errno = 0;

	char output[1];
	output[0] = c;
	write(STDOUT, output, 1, 0);

	return c;
}
