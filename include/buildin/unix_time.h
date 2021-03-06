#pragma once

#include <extern.h>

EXPOSEC long long to_unix_time(int year, int month, int day, int hour, int minute, int second);
EXPOSEC void from_unix_time(unsigned long int unixtime, int* year, int* month, int* day, int* hour, int* minute, int* second);
EXPOSEC void unix_time_to_string(unsigned long int unixtime, char* buffer);