#include <unistd.h>
#include <sys/delay.h>

int usleep(useconds_t usec) {
    delay(usec / 1000);
    return 0;
}