#include "../core/sysapi.h"

int test_getdelim() {
    char line[200];
    FILE *fp;
    int ret;
    char delims[] = {':', ':', ';', ',', '`', '$'};
    int iter;
    int counted_str = 0;

    fp = fopen("test_delims.file", "r");
    if (!fp)
        return -1;

    for (iter = 0; iter < sizeof(delims) / sizeof(delims[0]); iter++) {
        ret = sysapi_getdelim(line, sizeof(line), delims[iter], fp);
        if (ret >= 0) {
            printf("line is %s\n", line);
            counted_str++;
        } else if (ret < 0) {
            printf("ret is %d\n", ret);
            break;
        }
    }

    if (counted_str != (sizeof(delims) / sizeof(delims[0])))
        ret = 0;

    fclose(fp);

    return ret;
}
