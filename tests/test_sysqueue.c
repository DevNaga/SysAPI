#include "../core/sysapi_queue.h"

void cbfunc_show_elems(void *data, void *magic)
{
    int *i = data;

    printf("i value %d\n", *i);
}

int main(int argc, char **argv) {
    void *q;

    q = sysapi_queue_init();
    if (!q)
        return -1;

    int count = atoi(argv[1]);
    int i;

    for (i = 0; i < count; i++) {
        sysapi_queue_enque(&i, q);
    }

    sysapi_queue_deque(cbfunc_show_elems, NULL, q);
    sysapi_queue_deque_all(cbfunc_show_elems, NULL, q);

    sysapi_queue_deinit(NULL, NULL, q);

    return 0;
}

