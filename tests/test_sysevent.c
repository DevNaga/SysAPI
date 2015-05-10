#include "../sysapi.h"

void *evthr_ctx = NULL;
int s = 0;

void sapi_read_event_cb(void *cbctx)
{
    int *s = cbctx;
    char input[100];
    int len;

    memset(input, 0, sizeof(input));

    printf("address %d\n", *s);
    len = read(*s, input, sizeof(input));
    if (len > 0) {
        printf("read %d from input : %s\n", len, input);
        return;
    } else {
        printf("read error from %d\n", *s);
    }
}

int sock_tester()
{
    int ret = -1;

    evthr_ctx = sapi_event_system_init();
    printf("context %p\n", evthr_ctx);
    sapi_reg_read_event(s, evthr_ctx, &s, sapi_read_event_cb);

    return ret;
}

int main(int argc, char *argv[])
{
    int opt;
    int ret = -1;
    int sock_test = 0;

    while ((opt = getopt(argc, argv, "ts")) != -1) {
        switch (opt) {
            case 's':
                sock_test = 1;
            break;
            default:
                return -1;
        }
    }

    if (sock_test) {
        ret = sock_tester();
    }

    sapi_event_loop(evthr_ctx);

    sapi_event_system_deinit(evthr_ctx);

    return ret;
}

