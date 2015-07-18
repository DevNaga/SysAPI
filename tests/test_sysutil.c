#include "../core/sysapi_util.h"

int main(void) {
    int a = 1, b = 2;
    int failure = 0;
    int ret;

    sysapi_log_info("test", "This is an info msg\n");
    sysapi_log_warn("test: ", "This is a warning msg\n");
    sysapi_log_err("test: ", "This is an err msg\n");
    sysapi_log_info("testing", "%d %d\n", a, b);
    sysapi_log_norm("testing", "%d %d\n", a, b);
    printf("%s\n", (sysapi_get_arch() == SYSAPI_ARCH_64_BIT)? "64": "32");
    printf("%d\n", sysapi_get_rand());
    printf("%d\n", sysapi_get_rand_range(22));

    ret = test_get_line();
    if (ret < 0) {
        printf("get line test failure\n");
        failure++;
    }

    ret = test_getdelim();
    if (ret < 0) {
        printf("get delimiter test failure\n");
        failure++;
    }

    ret = sysapi_create_lockfile("/tmp/sysapi_test_lock.lock");
    if (ret == 0) {
        ret = sysapi_file_exist("/tmp/sysapi_test_lock.lock");
        if (ret != 0)
            failure++;
    }

    return failure;
}

