#include <stdbool.h>

#include <stdio.h>

int gets(char* buffer) {
	int buffer_len = 0;
	
	while (true) {
		char input = getchar();

		if (input == '\b') {
			buffer[buffer_len] = 0;
			buffer_len--;
			if (buffer_len == -1) {
				printf(" ");
				buffer_len = 0;
			}
		} else if (input == '\n') {
			break;
		} else {
			buffer[buffer_len] = input;
			buffer_len++;
		}
	}

	return buffer_len;
}