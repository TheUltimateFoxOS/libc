#pragma once

#include <extern.h>

#define SYS_SEEK_SET 0xff

enum seek_type {
	SEEK_SET = 1,
	SEEK_CUR,
	SEEK_END
};

EXPOSEC void seek_set(int fd, int offset, int mode);