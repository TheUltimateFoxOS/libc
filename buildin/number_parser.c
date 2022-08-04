#include <buildin/number_parser.h>

#include <stdbool.h>

char* __libc_parse_number(char* input, int* output) {
	bool hex = false;
	bool bin = false;
	bool dec = false;

	int start_offset = 0;

	if (input[0] == '0') {
		if (input[1] == 'x') {
			hex = true;
			start_offset = 2;
		} else if (input[1] == 'b') {
			bin = true;
			start_offset = 2;
		} else {
			dec = true;
		}
	} else {
		dec = true;
	}

	int number_system_base = 0;

	if (hex) {
		number_system_base = 16;
	} else if (bin) {
		number_system_base = 2;
	} else {
		number_system_base = 10;
	}

	int _number = 0;
	int idx = start_offset;

	while (input[idx] != '\0') {
		if (input[idx] >= '0' && input[idx] <= '9') {
			_number = _number * number_system_base + (input[idx] - '0');
		} else if (input[idx] >= 'a' && input[idx] <= 'f') {
			_number = _number * number_system_base + (input[idx] - 'a' + 10);
		} else if (input[idx] >= 'A' && input[idx] <= 'F') {
			_number = _number * number_system_base + (input[idx] - 'A' + 10);
		} else {
			break;
		}

		idx++;
	}

	*output = _number;

	return &input[idx];
}
