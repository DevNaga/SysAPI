#ifndef __SYSAPI_NET_H__
#define __SYSAPI_NET_H__

int sapi_net_tcp_server_create(char *ip, int port, int n_conns);

int sapi_unix_tcp_server_create(char *path, int n_conns);

void sapi_unix_tcp_server_destroy(int sock);

void sapi_inet_tcp_server_destroy(int sock);

int sapi_get_ifaddr(void *ctx, char *ifname, char *ifaddr);

void * sapi_lib_context_create(void);

void sapi_lib_context_destroy(void *libctx);

#endif
