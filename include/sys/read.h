#include <extern.h>

#define SYS_READ 6

#define STDIN 0

EXPOSEC void read(int fd, const void* buf, int count);