#pragma once

#include <stdint.h>
#include <extern.h>

typedef struct {
	uint64_t id;
	int speed;
	char manufacture[64];
	char version[64];
} cpu_info_t;

EXPOSEC int sm32_get_cpu_info(cpu_info_t* cpu_info);