#include "../sysapi_util.h"

int main(void) {
    sysapi_log_info("test", "This is an info msg\n");
    sysapi_log_warn("test: ", "This is a warning msg\n");
    sysapi_log_err("test: ", "This is an err msg\n");
}

