#ifndef __SYSAPI_NET_H__
#define __SYSAPI_NET_H__

int sapi_inet_tcp_server_create(char *ip, int port, int n_conns);

int sapi_inet_tcp_client_create(char *ip, int port);

int sapi_inet_tcp_transmit(int sock, void *data, int datalen);

int sapi_inet_tcp_receive(int sock, void *data, int datalen);

int sapi_unix_tcp_server_create(char *path, int n_conns);

int sapi_unix_tcp_client_create(char *path);

void sapi_unix_tcp_server_destroy(int sock);

void sapi_unix_tcp_client_destroy(int sock);

int sapi_unix_tcp_transmit(int sock, void *data, int datalen);

int sapi_unix_tcp_receive(int sock, void *data, int datalen);

void sapi_inet_tcp_server_destroy(int sock);

void sapi_inet_tcp_client_destroy(int sock);

int sapi_get_ifaddr(void *ctx, char *ifname, char *ifaddr);

void * sapi_lib_context_create(void);

void sapi_lib_context_destroy(void *libctx);

#endif
