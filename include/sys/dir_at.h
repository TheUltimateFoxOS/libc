#pragma once

#include <extern.h>

#include <stdbool.h>

#define MAX_DIR_NAME_LENGTH 256

enum dir_entry_type_e {
	ENTRY_FILE,
	ENTRY_DIR
};

typedef struct {
	char name[MAX_DIR_NAME_LENGTH];
	int idx;
	bool is_none;
	enum dir_entry_type_e type;
} dir_t;

EXPOSEC dir_t dir_at(int idx, const char* path);