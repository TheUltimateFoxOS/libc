#pragma once

#include <extern.h>

#define SYS_OPEN 9

EXPOSEC int open(const char* path, const char* mode);