#include "../core/sysapi_thpool.h"

void *worker;
int myint = 200;
int two = 300;

void printer(const char *func, int data)
{
    int i;

    for (i = 0; i < data; i++) {
        printf("my work %s prints %d\n", func, i);
    }
}

void test_work(void *priv)
{
    int *myintval = priv;

    printer(__func__, *myintval);
}

void test_work2(void *priv)
{
    int *myintval = priv;

    printer(__func__, *myintval);
}

int main(void) {
    worker = sapi_worker_create(test_work, &myint);
    printf("%p\n", worker);
    if (!worker) {
        printf("Failed to create a worker\n");
        return -1;
    }

    printf("worker...\n");
    if (sapi_queue_work(worker, test_work2, &two) < 0) {
        printf("Failed to queue a work\n");
        return -1;
    }

    sapi_start_work_all(worker);
    while (1);
    return 0;
}
