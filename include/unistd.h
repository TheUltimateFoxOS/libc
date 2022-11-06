#pragma once

#include <stdint.h>

typedef unsigned long useconds_t;

#define isatty(fd) 1

int usleep(useconds_t usec);