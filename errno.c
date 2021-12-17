#include <errno.h>
int __errno;

char* strerror(int errnum) {

	return errors[errnum];
}