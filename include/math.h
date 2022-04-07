#pragma once

#include <stdint.h>
#include <extern.h>

#include <stdio.h>

#define INFINITY (__builtin_inff ())
#define NAN (__builtin_nanf (""))

#define isinf(x) __builtin_isinf (x)
#define isnan(x) __builtin_isnan (x)
#define isfinite(x) __builtin_isfinite (x)

EXPOSEC int signbit(double x);

EXPOSEC int abs(int x);
EXPOSEC double fabs (double x);

#define define_stub_1p(name) \
	EXPOSEC double name(double x);

#define define_stub_2p(name) \
	EXPOSEC double name(double x, double y);

#define define_stub_func_1p(name) \
	EXPOSEC double name(double x) { \
		return __builtin_##name (x); \
	}

#define define_stub_func_2p(name) \
	EXPOSEC double name(double x, double y) { \
		return __builtin_##name (x, y); \
	}

define_stub_1p(acos);
define_stub_1p(asin);
define_stub_1p(atan);
define_stub_2p(atan2);
define_stub_1p(cos);
define_stub_1p(sin);
define_stub_1p(tan);
define_stub_1p(log);
define_stub_1p(exp);
define_stub_1p(floor);
define_stub_1p(ceil);
define_stub_2p(fmod);
define_stub_1p(sqrt);