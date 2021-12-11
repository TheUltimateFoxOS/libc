#pragma once

#include <extern.h>

#define SYS_OPEN 0xff

EXPOSEC int open(const char* path, const char* mode);