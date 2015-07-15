#include "../core/sysapi.h"

int test_get_line() {
    int ret;
    FILE *fp;
    char *file = "./test_getline.c";
    int line_count = 0;

    fp = fopen(file, "r");
    if (!fp)
        return -1;

    while (1) {
        char buf[200];

        ret = sysapi_get_line(buf, fp, sizeof(buf));
        if (ret < 0) {
            printf("end of file\n");
            break;
        } else {
            line_count++;
        }
    }

    fclose(fp);
    printf("line count %d\n", line_count);

    return 0;
}
