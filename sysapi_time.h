#ifndef __SYSAPI_TIME_H__
#define __SYSAPI_TIME_H__

long sapi_get_time_sec();

uint64_t sapi_get_time_msec();

int sapi_is_dst_active();

struct sapi_time {
	int sec;
	int min;
	int hour;
	int day;
	int mon;
	int year;
};

int sapi_get_cur_caltime(struct sapi_time *);

int sapi_get_cur_monstr(char *);

#endif

