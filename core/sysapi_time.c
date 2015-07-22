#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include "sysapi_time.h"

long sapi_get_time_sec()
{
    return time(0);
}

uint64_t sapi_get_time_msec()
{
    struct timeval tv;

    gettimeofday(&tv, 0);

    return ((uint64_t)tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

int sapi_is_dst_active()
{
    time_t now;
    struct tm *t;

    now = time(0);
    t = localtime(&now);

    // we are not handling for the DST unavailable flag here
    return t->tm_isdst > 0? 1: 0;
}

// the first argument here is for thread safety
int sapi_get_cur_caltime(struct sapi_time *sapi_time)
{
    int ret;
    time_t now;
    struct tm *t;

    ret = -1;
    now = time(0);
    t = localtime(&now);
    if (t) {
        ret = 0;
        sapi_time->sec = t->tm_sec;
        sapi_time->min = t->tm_min;
        sapi_time->hour = t->tm_hour;
        sapi_time->day = t->tm_mday;
        sapi_time->mon = t->tm_mon;
        sapi_time->year = t->tm_year + 1900; // get current year
    }

    return ret;
}

int sysapi_snprintf_cur_caltime(char *buf, int len)
{
    struct sapi_time sapi_time;
    int ret;

    ret = sapi_get_cur_caltime(&sapi_time);
    if (ret == -1)
        return ret;

    return snprintf(buf, len, "%02d:%02d:%04d: %02d:%02d:%02d",
                    sapi_time.day,
                    sapi_time.mon + 1,
                    sapi_time.year,
                    sapi_time.hour,
                    sapi_time.min,
                    sapi_time.sec);
}

int sapi_get_cur_monstr(char *mon)
{
    int ret = -1;
    char *months[] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
#define MON_LEN (sizeof(months) / sizeof(months[0]))
    struct sapi_time cur;

    ret = sapi_get_cur_caltime(&cur);
    if (ret < 0)
        return ret;

    ret = 0;
    strcpy(mon, months[cur.mon]);
    return ret;
}

#ifdef CONFIG_SYSAPI_TIME_TEST
int main(void)
{
    printf("%d\n", sapi_is_dst_active());

    return 0;
}
#endif

int sysapi_create_interval_timer(long secs, long usecs)
{
    return __sysapi_create_timer(secs, usecs, 1);
}

int sysapi_create_oneshot_timer(long secs, long usecs)
{
    return __sysapi_create_timer(secs, usecs, 0);
}

int __sysapi_create_timer(long secs, long usec, int interval_timer)
{
    struct itimerspec it_sp;
    int ret;
    int timer_fd;

    timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timer_fd < 0)
        return -1;

    memset(&it_sp, 0, sizeof(struct itimerspec));

    it_sp.it_value.tv_sec = secs;
    it_sp.it_value.tv_nsec = usec * 1000;
    if (interval_timer) {
        it_sp.it_interval.tv_sec = secs;
        it_sp.it_interval.tv_nsec = usec * 1000;
    }

    ret = timerfd_settime(timer_fd, 0, &it_sp, NULL);
    if (ret < 0) {
        close(timer_fd);
        return -1;
    }

    return timer_fd;
}

