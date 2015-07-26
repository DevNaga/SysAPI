#ifndef __SYSAPI_TIME_H__
#define __SYSAPI_TIME_H__

// get current time in seconds
long sapi_get_time_sec(void);

// get current time in millseconds
uint64_t sapi_get_time_msec(void);

// is the DST active ?
int sapi_is_dst_active(void);

// this is the time format structure
// converting the gmtime / localtime calls into the standard
// time format. See below API to get time in respective time standard
struct sapi_time {
	int sec;
	int min;
	int hour;
	int day;
	int mon;
	int year;
};

// get current calendar time in the current timezone (for me its an IST)
int sapi_get_cur_caltime(struct sapi_time *);

// get the current local time in the string pointed to buf and print until its 'len' bytes
int sysapi_snprintf_cur_caltime(char *buf, int len);

// get current month in string format
int sapi_get_cur_monstr(char *);

// get the current utc time
int sapi_get_cur_utctime(struct sapi_time *sapi_time);

// get the current utc time in the string format (similar to sysapi_snprintf_cur_caltime)
int sysapi_snprintf_cur_utctime(char *buf, int len);

#endif

