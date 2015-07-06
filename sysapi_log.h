#ifndef __SYSAPI_LOG_H__
#define __SYSAPI_LOG_H__

#include "sysapi_net.h"

int sapi_open_syslog(void);

int sapi_write_syslog_msg(int syslog_sock, char *msg, int len);

void sapi_close_syslog(int syslog_sock);

#endif
