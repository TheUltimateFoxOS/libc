#pragma once

#include <extern.h>

#include <stdbool.h>
enum dir_entry_type_e {
	ENTRY_FILE,
	ENTRY_DIR
};

typedef struct {
	char name[256];
	int idx;
	bool is_none;
	enum dir_entry_type_e type;
} dir_t;

EXPOSEC dir_t dir_at(int idx, const char* path);