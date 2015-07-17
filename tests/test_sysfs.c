#include "../core/sysapi.h"

void test_dir_cb(char *filename, sysapi_file_type type, void *app_ctx)
{
    printf("file %s\n", filename);
}

void test_file_cb(char *filedata, int len, void *app_ctx)
{
    printf("data %s", filedata);
}

void test_dir_walk(char *parent, sysapi_file_type type, char *file, void *app_ctx)
{
    switch (type) {
        case SYSAPI_FILE_TYPE_REGFILE:
            printf("file ");
        break;
        case SYSAPI_FILE_TYPE_DIRECT:
            printf("directory ");
        break;
    }
    printf(" %s parent %s\n", file, parent);
}

void test_list_dir(char *dir, void *ctx)
{
    printf("dir %s\n", dir);
}

/// FILE exist test case
//

int test_file_exist()
{
    char non_existent[] = "fksjkfiuwaiekwfaew";
    char existent[] = "test_sysfs.c";
    int ret;

    ret = sysapi_file_exist(existent);
    if (ret < 0)
        return -1;

    ret = sysapi_file_exist(non_existent);
    if (ret >= 0)
        return -1;

    return 0;
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
    ret = sysapi_describe_link("/media/sf_github/SysAPI/doc1/", path, sizeof(path));
    ret = sysapi_touch("test1");
    ret = sysapi_create_pidfile("test1.pid");
    ret = sysapi_list_dir(dir, test_list_dir, NULL);
    ret = test_file_exist();
    return ret;
}
