#pragma once

#include <extern.h>
#include <stdint.h>

typedef struct {
	uint64_t total;
	uint64_t free;
	uint64_t used;
	uint64_t reserved;
} memory_info_t;

EXPOSEC memory_info_t memory_info();