#pragma once
#include <extern.h>

#define SYS_RESOLVE_SYMBOL 3

EXPOSEC void* resolve_symbol(char* name);