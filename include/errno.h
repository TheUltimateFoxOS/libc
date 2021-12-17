#pragma once

#include <extern.h>

#define errno __errno
extern int __errno;

#define ERANGE 1

static char* errors[] = {
	"Success",
	"ERANGE"
};

EXPOSEC char* strerror(int errnum);
