#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include "sysapi_log.h"

int sapi_open_syslog()
{
    char *log_sock = "/dev/log";

    return sapi_unix_tcp_client_create(log_sock);
}

int sapi_write_syslog_msg(int syslog_sock, char *msg, int len)
{
    return sapi_unix_tcp_transmit(syslog_sock, msg, len);
}

void sapi_close_syslog(int syslog_sock)
{
    sapi_unix_tcp_client_destroy(syslog_sock);
}

void sysapi_syslog_emerge(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_EMERG, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_perror(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_PERROR, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_pid(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_PID, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_cons(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_CONS, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_notice(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_NOTICE, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_err(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_ERR, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_alert(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_ALERT, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_info(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_INFO, fmt, ap);
    va_end(ap);
}

void sysapi_syslog_debug(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsyslog(LOG_DEBUG, fmt, ap);
    va_end(ap);
}

