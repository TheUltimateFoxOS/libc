#pragma once

#include <extern.h>
#include <sys/thread.h>

#define START_MARKER 0xdeadbeef

EXPOSEC void __libc_kill_childs(void);
EXPOSEC void __libc_init_childs_list(void);

EXPOSEC task_t* create_thread(void* entry);