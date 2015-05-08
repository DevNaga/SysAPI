#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// AF_INET for now
int sapi_net_tcp_server_create(char *ip, int port, int n_conns)
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

