#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
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

