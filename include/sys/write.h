#pragma once
#include <extern.h>

#define STDOUT 1
#define STDERR 2

EXPOSEC void write(int fd, const void* buf, int count, int offset);