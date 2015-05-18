#include "../sysapi.h"

void test_dir_cb(char *filename, sysapi_file_type type, void *app_ctx)
{
    printf("file %s\n", filename);
}

void test_file_cb(char *filedata, int len, void *app_ctx)
{
    printf("data %s", filedata);
}

int main(void)
{
    char *dir = ".";
    char *file = "test_sysnet.c";
    int ret;

    ret = sysapi_dir_read(dir, test_dir_cb, NULL);
    ret = sysapi_read_binfile(file, test_file_cb, NULL);

    return ret;
}

