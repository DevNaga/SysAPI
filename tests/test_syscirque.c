#include "../sysapi.h"

void cb_caller(void *cbdata, void *data)
{
    int *i;

    i = data;

    printf("%d ", *i);
}

int main(void)
{
    int i;
    int array[100];
    void *handler;

    handler = sysapi_cirque_init(100);

    for (i = 0; i < 10; i++) {
        array[i] = i;
        sysapi_cirque_add(handler, &(array[i]));
    }

    sysapi_cirque_for_each(handler, NULL, cb_caller);

    sysapi_cirque_deinit(handler);

    printf("\n");

    handler = sysapi_cirque_init(100);

    for (i = 0; i < 10; i++) {
        array[i] = i;
        sysapi_cirque_add(handler, &(array[i]));
    }

    sysapi_cirque_for_each(handler, NULL, cb_caller);

    sysapi_cirque_display(handler);

    sysapi_cirque_deinit(handler);

    printf("\n");
    return 0;
}

