#pragma once

#include <sys/spawn.h>

EXPOSEC task_t* thread(void* entry, bool clone_cwd);