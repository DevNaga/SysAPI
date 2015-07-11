#ifndef __SYSAPI_TIME_H__
#define __SYSAPI_TIME_H__

long sapi_get_time_sec(void);

uint64_t sapi_get_time_msec(void);

int sapi_is_dst_active(void);

struct sapi_time {
	int sec;
	int min;
	int hour;
	int day;
	int mon;
	int year;
};

int sapi_get_cur_caltime(struct sapi_time *);

int sysapi_snprintf_cur_caltime(char *buf, int len);

int sapi_get_cur_monstr(char *);

#endif

