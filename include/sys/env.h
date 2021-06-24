#pragma once
#pragma once
#include <extern.h>

#define SYS_ENV 5

#define ENV_ARGV 0
#define ENV_ENVP 1
#define ENV_ERRNO 2

EXPOSEC char** env(int mode);
EXPOSEC void env_set(int mode, void* data);