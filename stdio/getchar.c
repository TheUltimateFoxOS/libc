#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/read.h>

char getchar() {
	errno = 0;

	char input[1];
	read(STDIN, input, 1);

	if (errno == 0xded) {
		printf("Other procces is already reading from stdin!");
		abort();
	}

	return input[0];
}