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
    char *addr;

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

int sapi_unix_tcp_server_create(char *path, int n_conns)
{
    int ret;

    struct sockaddr_un serv = {
        .sun_family = AF_UNIX,
        .sun_path = strlen(path) + 1,
#ifdef CONFIG_OS_BSD
        .sun_len = SUN_LEN(&serv),
#endif
    };

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

void sapi_unix_tcp_server_destroy(int sock)
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

    sock = socket(AF_INET, SOCK_STREAM, 0);
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

void sapi_inet_tcp_server_destroy(int sock)
{
    close(sock);
}
