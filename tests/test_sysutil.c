#include "../sysapi_util.h"

int main(void) {
    int a = 1, b = 2;
    sysapi_log_info("test", "This is an info msg\n");
    sysapi_log_warn("test: ", "This is a warning msg\n");
    sysapi_log_err("test: ", "This is an err msg\n");
    sysapi_log_info("testing", "%d %d\n", a, b);
    sysapi_log_norm("testing", "%d %d\n", a, b);
    printf("%d\n", sysapi_get_arch());
    printf("%d\n", sysapi_get_rand());
    printf("%d\n", sysapi_get_rand_range(22));
}

