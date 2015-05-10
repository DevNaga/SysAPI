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
    } else {
        printf("get mac test fails\n");
    }

    return ret;
}

int main(int argc, char *argv[])
{
    int ret = -1;
    int opt;
    char *ifname = NULL;

    while ((opt = getopt(argc, argv, "m:")) != -1) {
        switch (opt) {
            case 'm':
                ifname = optarg;
            break;
        }
    }

    libctx = sapi_lib_context_create();
    if (!libctx)
        return -1;

    if (ifname) {
        ret = get_mac_addr(ifname);
    }

    sapi_lib_context_destroy(libctx);

    return ret;
}

