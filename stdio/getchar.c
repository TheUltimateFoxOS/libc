#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/read.h>

char getchar() {
	errno = 0;

	char input[1];
	read(STDIN, input, 1, 0);

	return input[0];
}