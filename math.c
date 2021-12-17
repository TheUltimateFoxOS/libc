#include <math.h>

int signbit(double x) {
	return __builtin_signbit(x);
}

define_stub_func_1p(acos);
define_stub_func_1p(asin);
define_stub_func_1p(atan);
define_stub_func_2p(atan2);
define_stub_func_1p(cos);
define_stub_func_1p(sin);
define_stub_func_1p(tan);
define_stub_func_1p(log);
define_stub_func_1p(exp);
define_stub_func_1p(floor);
define_stub_func_1p(ceil);
define_stub_func_1p(fabs);
define_stub_func_2p(fmod);
define_stub_func_2p(pow);
define_stub_func_1p(sqrt);