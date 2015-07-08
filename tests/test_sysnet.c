#include "../sysapi.h"

void *libctx;

int get_mac_addr(char *ifname)
{
    char ifaddr[40];
    int ret = -1;

    memset(ifaddr, 0, sizeof(ifaddr));

    ret = sapi_get_ifaddr(libctx, ifname, ifaddr);
    if (ret == 0) {
        printf("addr : %s\n", ifaddr);
    } else if (ret == -LSAPI_INET_ADDR_NOTAVAIL) {
        printf("get ipaddr test fails: no address\n");
    }

    return ret;
}

int get_mtu()
{
    int mtu = sysapi_get_mtu("enp0s3");
    if (mtu < 0) {
        printf("get mtu test fails\n");
        return -1;
    }

    printf("mtu %d\n", mtu);

    return 0;
}

int get_so_max_conn()
{
    int maxconn = sapi_get_max_conn();

    if (maxconn > 0) {
        printf("maxconn %d\n", maxconn);
        return 0;
    }

    return -1;
}

int set_so_max_conn()
{
    int maxconn = 200;

    sapi_set_max_conn(maxconn);

    if (maxconn != sapi_get_max_conn()) {
        printf("failed to set\n");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int ret = -1;
    int opt;
    char *ifname = NULL;
    int mc = 0;
    int mtu = 0;
    int nm = 0;

    if (argc == 1)
        return -1;

    while ((opt = getopt(argc, argv, "m:cMn")) != -1) {
        switch (opt) {
            case 'm':
                ifname = optarg;
            break;
            case 'c':
                mc = 1;
            break;
            case 'M':
                mtu = 1;
            break;
            case 'n':
                nm = 1;
            break;
        }
    }

    libctx = sapi_lib_context_create();
    if (!libctx)
        return -1;

    if (ifname) {
        ret = get_mac_addr(ifname);
    } else if (mc) {
        ret = get_so_max_conn();
        ret = set_so_max_conn();
    } else if (mtu) {
        ret = get_mtu();
    } else if (nm) {
        char net[30];
        ret = sysapi_get_netmask("eth0", net);
        printf("netmask %s\n", net);
    }

    sapi_lib_context_destroy(libctx);

    return ret;
}
