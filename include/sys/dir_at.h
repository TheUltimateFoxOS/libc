#pragma once

#include <extern.h>

#include <stdbool.h>

typedef struct {
	char name[256];
	int idx;
	bool is_none;
} dir_t;

EXPOSEC dir_t dir_at(int idx, const char* path);