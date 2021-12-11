#pragma once
#include <extern.h>

#define SYS_RESOLVE_SYMBOL 0xff

EXPOSEC void* resolve_symbol(char* name);