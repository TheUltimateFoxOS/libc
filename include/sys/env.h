#pragma once
#pragma once
#include <extern.h>

#define ENV_ARGV 0
#define ENV_ENVP 1
#define ENV_ERRNO 2
#define ENV_SIGHANDLER 3
#define ENV_SET_CWD 4
#define ENV_GET_CWD 5
#define ENV_ACPI_SHUTDOWN 6
#define ENV_ENVP_SET 7
#define ENV_PIPE_DISABLE_ENABLE 8
#define ENV_GET_TASK 9
#define ENV_READ_RUNNING_TASKS 10
#define ENV_ACPI_REBOOT 11
#define ENV_GET_LOADED_MODULES 12

EXPOSEC char** env(int mode);
EXPOSEC void env2(int mode);
EXPOSEC void env_set(int mode, void* data);

EXPOSEC void env_set2(int mode, int data, void* data2);
// EXPOSEC void env_set3(int mode, int data);