#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

struct sapi_lib_context {
    int drv_fd;
};

void *sapi_lib_context_create(void)
{
    struct sapi_lib_context *libctx;

    libctx = calloc(1, sizeof(struct sapi_lib_context));
    if (!libctx)
        return NULL;

    libctx->drv_fd = -1;

    return libctx;
}

void sapi_lib_context_destroy(void *ctx)
{
    struct sapi_lib_context *libctx = ctx;

    if (libctx->drv_fd > 0)
        close(libctx->drv_fd);

    free(libctx);
}

int sapi_get_ifaddr(void *ctx, char *ifname, char *ifaddr)
{
    struct ifreq ifr;
    struct sapi_lib_context *libctx = ctx;
    int ret = -1;

    memset(&ifr, 0, sizeof(ifr));

    if (libctx->drv_fd < 0) {
        libctx->drv_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (libctx->drv_fd < 0)
            return ret;
    }

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, ifname, strlen(ifname) + 1);

    ret = ioctl(libctx->drv_fd,  SIOCGIFADDR, &ifr);
    if (ret < 0)
        return ret;

    strcpy(ifaddr, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    return (ret >= 0) ? 0: -1;
}

int sysapi_get_mtu(char *ifname)
{
    int ret;
    int fd;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
        return -1;

    struct ifreq ifr;

    ifr.ifr_addr.sa_family = AF_INET;
    strcpy(ifr.ifr_name, ifname);

    ret = ioctl(fd, SIOCGIFMTU, &ifr);
    if (ret < 0) {
        close(fd);
        return -1;
    }

    close(fd);
    ret = ifr.ifr_mtu;

    return ret;
}

int sysapi_get_netmask(char *ifname, char *nmask)
{
    int ret;
    struct sockaddr_in *_nmask;
    int fd;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
        return -1;

    struct ifreq ifr;

    ifr.ifr_addr.sa_family = AF_INET;
    strcpy(ifr.ifr_name, ifname);

    ret = ioctl(fd, SIOCGIFNETMASK, &ifr);
    if (ret < 0) {
        close(fd);
        return -1;
    }

    _nmask = (struct sockaddr_in *)(&ifr.ifr_netmask);
    strcpy(nmask, inet_ntoa(_nmask->sin_addr));

    close(fd);

    return 0;
}

int sapi_unix_tcp_server_create(char *path, int n_conns)
{
    int ret;

    struct sockaddr_un serv = {
        .sun_family = AF_UNIX,
#ifdef CONFIG_OS_BSD
        .sun_len = SUN_LEN(&serv),
#endif
    };

    strcpy(serv.sun_path, path);

    int sock;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
        return -1;

    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
        goto err_bind;

    ret = listen(sock, n_conns);
    if (ret < 0)
        goto err_listen;

    return sock;

err_listen:
err_bind:
    close(sock);
    return -1;
}

int sapi_unix_tcp_client_create(char *path)
{
    int ret;

    struct sockaddr_un serv = {
        .sun_family = AF_UNIX,
    };

    strcpy(serv.sun_path, path);

    int sock;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
        return -1;

    ret = connect(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
        goto err_connect;

    return sock;

err_connect:
    close(sock);
    return -1;
}

void sapi_unix_tcp_server_destroy(int sock)
{
    close(sock);
}

void sapi_unix_tcp_client_destroy(int sock)
{
    close(sock);
}

// AF_INET for now
int sapi_inet_tcp_server_create(char *ip, int port, int n_conns)
{
    int ret;

    struct sockaddr_in serv = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(ip),
        .sin_port = htons(port)
    };

    int sock;
    int opt = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return -1;

    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret < 0)
        goto err_sockopt;
    
    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
        goto err_bind;

    ret = listen(sock, n_conns);
    if (ret < 0)
        goto err_listen;

    return sock;

err_listen:
err_bind:
err_sockopt:
    close(sock);
    return -1;
}

int sapi_inet_tcp_client_create(char *ip, int port)
{
    int ret;

    struct sockaddr_in serv = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(ip),
        .sin_port = htons(port)
    };

    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return -1;

    ret = connect(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
        goto err_connect;

    return sock;

err_connect:
    close(sock);
    return -1;
}

int _sapi_inet_tcp_transmit(int sock, void *data, int datalen)
{
    return send(sock, (void *)data, datalen, 0);
}

int sapi_unix_tcp_transmit(int sock, void *data, int datalen)
{
    return _sapi_inet_tcp_transmit(sock, data, datalen);
}

int sapi_inet_tcp_transmit(int sock, void *data, int datalen)
{
    return _sapi_inet_tcp_transmit(sock, data, datalen);
}

int _sapi_inet_tcp_receive(int sock, void *data, int datalen)
{
    return recv(sock, (void *)data, datalen, 0);
}

int sapi_unix_tcp_receive(int sock, void *data, int datalen)
{
    return _sapi_inet_tcp_receive(sock, data, datalen);
}

int sapi_inet_tcp_receive(int sock, void *data, int datalen)
{
    return _sapi_inet_tcp_receive(sock, data, datalen);
}

void sapi_inet_tcp_server_destroy(int sock)
{
    close(sock);
}

void sapi_inet_tcp_client_destroy(int sock)
{
    close(sock);
}

int sapi_inet_udp_server_create(char *ip_addr, int port)
{
    int sock;
    int ret;

    struct sockaddr_in serv;

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(ip_addr);
    serv.sin_port = htons(port);

    int opt = 1;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        return -1;

    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret < 0)
        goto err_sockopt;
    
    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
        goto err_sock;

    return sock;

err_sockopt:
err_sock:
    close(sock);
    return -1;
}

void sapi_inet_udp_server_destroy(int sock)
{
    close(sock);
}

int sapi_inet_udp_client_create(char *ip_addr, int port, struct sockaddr_in *serv)
{
    int sock;
    
    serv->sin_family = AF_INET;
    serv->sin_addr.s_addr = inet_addr(ip_addr);
    serv->sin_port = htons(port);
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        return -1;
    
    return sock;
}

void sapi_inet_udp_client_destroy(int sock)
{
    close(sock);
}

#define SOMAXCON_NET "/proc/sys/net/core/somaxconn"
int sapi_get_max_conn()
{
    int fd;
    int ret;
    char buf[10];

    fd = open(SOMAXCON_NET, O_RDONLY);
    if (fd < 0)
        return -1;

    ret = read(fd, buf, sizeof(buf));
    if (ret > 0)
        ret = atoi(buf);

    close(fd);

    if (ret >= 0)
        return ret;

    return -1;
}

int sapi_set_max_conn(int conn)
{
    int fd;
    int ret;
    char buf[10];

    fd = open(SOMAXCON_NET, O_WRONLY);
    if (fd < 0)
        return -1;

    sprintf(buf, "%d\n", conn);
    ret = write(fd, buf, strlen(buf));

    close(fd);
    return ret > 0 ? 0: -1;
}

#undef SOMAXCON_NET

static int __sapi_sock_set_optint(int sock, int so_lvl, int opt_name)
{
    int opt = 1;
    
    return setsockopt(sock, so_lvl, opt_name, &opt, sizeof(opt));
}

static int __sapi_sock_reset_optint(int sock, int so_lvl, int opt_name)
{
    int opt = 0;
    
    return setsockopt(sock, so_lvl, opt_name, &opt, sizeof(opt));
}

int sapi_sock_set_reuseaddr(int sock)
{
    return __sapi_sock_set_optint(sock, SOL_SOCKET, SO_REUSEADDR);
}

int sapi_sock_reset_reuseaddr(int sock)
{
    return __sapi_sock_reset_optint(sock, SOL_SOCKET, SO_REUSEADDR);
}

int sapi_sock_set_debug(int sock)
{
    return __sapi_sock_set_optint(sock, SOL_SOCKET, SO_DEBUG);
}

int sapi_sock_reset_debug(int sock)
{
    return __sapi_sock_reset_optint(sock, SOL_SOCKET, SO_DEBUG);
}

int sapi_sock_set_broadcast(int sock)
{
    return __sapi_sock_set_optint(sock, SOL_SOCKET, SO_BROADCAST);
}

int sapi_sock_reset_broadcast(int sock)
{
    return __sapi_sock_reset_optint(sock, SOL_SOCKET, SO_BROADCAST);
}

int sapi_sock_set_keepalive(int sock)
{
    return __sapi_sock_set_optint(sock, SOL_SOCKET, SO_KEEPALIVE);
}

int sapi_sock_reset_keepalive(int sock)
{
    return __sapi_sock_reset_optint(sock, SOL_SOCKET, SO_KEEPALIVE);
}

int __sapi_get_sock_type(int sock, char *socket_type)
{
    char *socktypes[] = {
        "tcp",
        "udp",
        "unknown",
    };
    
    int type = -1;
    int typelen = sizeof(type);
    int ret;
    
    ret = getsockopt(sock, SOL_SOCKET, SO_TYPE, &type, &typelen);
    if (ret < 0) {
        return -1;
    }
    
    if (type > sizeof(socktypes) / sizeof(socktypes[0])) {
        return -1;
    }
    
    socket_type = socktypes[type - 1];
    return 0;
}

int sapi_get_socktype(int sock, char *socket_type)
{
    return __sapi_get_sock_type(sock, socket_type);
}

int sapi_get_sndbufsize(int sock)
{
    int size;
    socklen_t sizelen = sizeof(size);
    int ret;
    
    ret = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &size, &sizelen);
    if (ret < 0) {
        return -1;
    }
    
    return size;
}

int sapi_get_rcvbufsize(int sock)
{
    int size;
    socklen_t sizelen = sizeof(size);
    int ret;
    
    ret = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &size, &sizelen);
    if (ret < 0) {
        return -1;
    }
    
    return size;
}
