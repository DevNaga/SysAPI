#include "../sysapi.h"

void test_dir_cb(char *filename, sysapi_file_type type, void *app_ctx)
{
    printf("file %s\n", filename);
}

void test_file_cb(char *filedata, int len, void *app_ctx)
{
    printf("data %s", filedata);
}

void test_dir_walk(char *parent, char *file, void *app_ctx)
{
    printf("file %s parent %s\n", file, parent);
}

int main(void)
{
    char *dir = ".";
    char *file = "test_sysnet.c";
    char path[200];
    int ret;

    ret = sysapi_dir_read(dir, test_dir_cb, NULL);
    ret = sysapi_read_binfile(file, test_file_cb, NULL);
    ret = sysapi_dir_walk(dir, test_dir_walk, NULL);
    ret = sysapi_describe_link("/media/sf_github/SysAPI/readme", path, sizeof(path));
    return ret;
}

