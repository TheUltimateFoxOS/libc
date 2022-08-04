#pragma once

#include <extern.h>

#include <stdint.h>

EXPOSEC void __libc_sighandler(uint8_t signum);
EXPOSEC void __libc_intr_sighandler(uint8_t signum);
EXPOSEC char* __libc_get_exception_name(int exc);