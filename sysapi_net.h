#ifndef __SYSAPI_NET_H__
#define __SYSAPI_NET_H__

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>

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

int sapi_get_rcvbufsize(int sock);

int sapi_get_sndbufsize(int sock);

int sapi_get_socktype(int sock, char *socket_type);

int sapi_sock_reset_keepalive(int sock);

int sapi_sock_set_keepalive(int sock);

int sapi_sock_reset_broadcast(int sock);

int sapi_sock_set_broadcast(int sock);

int sapi_sock_reset_debug(int sock);

int sapi_sock_set_debug(int sock);

int sapi_sock_reset_reuseaddr(int sock);

int sapi_sock_set_reuseaddr(int sock);

int sapi_set_max_conn(int conn);

int sapi_get_max_conn(void);

int sapi_inet_udp_client_create(char *ip_addr, int port,
		                        struct sockaddr_in *serv);

void sapi_inet_udp_client_destroy(int sock);

void sapi_inet_udp_server_destroy(int sock);

int sapi_inet_udp_server_create(char *ip_addr, int port);

int sysapi_get_netmask(char *ifname, char *nmask);

int sysapi_get_mtu(char *ifname);

int sysapi_get_macaddr(char *ifname, uint8_t *macaddr);

int sysapi_is_wdev(char *ifname);

int sysapi_get_wlan_rssi(char *ifname, int *rss);

int sysapi_is_dev_broadcast(char *ifname);

int sysapi_is_dev_lo(char *ifname);

int sysapi_get_txqlen(char *ifname);

#endif
