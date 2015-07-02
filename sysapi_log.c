#include "sysapi_net.h"

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
