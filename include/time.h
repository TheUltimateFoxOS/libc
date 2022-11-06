#pragma once

#include <stdint.h>

#include <extern.h>

#define clock_t uint64_t
#define time_t long long

#define CLOCKS_PER_SEC __libc_ticks_per_second()

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

EXPOSEC time_t time(time_t *tp);
EXPOSEC time_t mktime(struct tm *tp);
EXPOSEC struct tm *gmtime(const time_t *tp);
EXPOSEC struct tm *localtime(const time_t *tp);
EXPOSEC clock_t clock();

EXPOSEC clock_t __libc_ticks_per_second();