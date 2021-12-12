#pragma once
#pragma once
#include <extern.h>

#define ENV_ARGV 0
#define ENV_ENVP 1
#define ENV_ERRNO 2
#define ENV_SIGHANDLER 3

EXPOSEC char** env(int mode);
// EXPOSEC void env2(int mode);
EXPOSEC void env_set(int mode, void* data);

EXPOSEC void env_set2(int mode, int data, void* data2);
// EXPOSEC void env_set3(int mode, int data);