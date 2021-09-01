#pragma once
#pragma once
#include <extern.h>

#define SYS_ENV 5

#define ENV_ARGV 0
#define ENV_ENVP 1
#define ENV_ERRNO 2
#define ENV_SIGHANDLER 3
#define ENV_KEYMAP 4
#define ENV_KEYBOARD_DEBUG 5

enum keyboard_layout {
	keymap_de_e = 0,
	keymap_fr_e = 1,
	keymap_us_e = 2
};

EXPOSEC char** env(int mode);
EXPOSEC void env_set(int mode, void* data);

EXPOSEC void env_set2(int mode, int data, void* data2);
EXPOSEC void env_set3(int mode, int data);