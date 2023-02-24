#include <time.h>

#include <sys/time.h>
#include <sys/clock.h>

#include <stdlib.h>

time_t time(time_t *tp) {
	time_t t = _time();
	if (tp) {
		*tp = t;
	}

	return t;
}

time_t mktime(struct tm *tp) {
	time_t t = _time();
	struct tm tm = *tp;

	if (tm.tm_year < 70) {
		tm.tm_year += 100;
	}

	if (tm.tm_mon < 0) {
		tm.tm_mon = 0;
	} else if (tm.tm_mon > 11) {
		tm.tm_mon = 11;
	}

	if (tm.tm_mday < 1) {
		tm.tm_mday = 1;
	} else if (tm.tm_mday > 31) {
		tm.tm_mday = 31;
	}

	if (tm.tm_hour < 0) {
		tm.tm_hour = 0;
	} else if (tm.tm_hour > 23) {
		tm.tm_hour = 23;
	}

	if (tm.tm_min < 0) {
		tm.tm_min = 0;
	} else if (tm.tm_min > 59) {
		tm.tm_min = 59;
	}

	if (tm.tm_sec < 0) {
		tm.tm_sec = 0;
	} else if (tm.tm_sec > 59) {
		tm.tm_sec = 59;
	}

	return t;
}

struct tm *gmtime(const time_t *tp) {
	struct tm *tm = malloc(sizeof(struct tm));
	time_t t = *tp;

	tm->tm_sec = t % 60;
	t /= 60;
	tm->tm_min = t % 60;
	t /= 60;
	tm->tm_hour = t % 24;
	t /= 24;
	tm->tm_wday = (t + 4) % 7;
	t /= 7;
	tm->tm_mday = t + 1;
	t = t / 4;
	tm->tm_mon = t % 12;
	t /= 12;
	tm->tm_year = t - 69;
	tm->tm_isdst = 0;

	return tm;
}

struct tm *localtime(const time_t *tp) {
	struct tm *tm = malloc(sizeof(struct tm));
	time_t t = *tp;

	tm->tm_sec = t % 60;
	t /= 60;
	tm->tm_min = t % 60;
	t /= 60;
	tm->tm_hour = t % 24;
	t /= 24;
	tm->tm_wday = (t + 4) % 7;
	t /= 7;
	tm->tm_mday = t + 1;
	t = t / 4;
	tm->tm_mon = t % 12;
	t /= 12;
	tm->tm_year = t - 69;
	tm->tm_isdst = 0;

	return tm;
}

clock_t clock() {
	return (clock_t) _clock();
}

double difftime(time_t time1, time_t time2) {
	if (time1 < time2) {
		return (double) (time2 - time1);
	} else {
		return (double) (time1 - time2);
	}
}

clock_t __libc_ticks_per_second() {
	return (clock_t) _clock_ticks_per_second();
}