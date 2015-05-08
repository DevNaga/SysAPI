#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

long sapi_get_time_sec()
{
    return time(0);
}

