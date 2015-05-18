#include "sysapi_fs.h"

int sysapi_dir_read(char *dirpath,
                    void (*callback)(char *filename, sysapi_file_type type, void *app_ctx),
                    void *app_ctx)
{
    DIR *dirp;
    struct dirent *entry;
    char path[300];

    dirp = opendir(dirpath);
    if (!dirp)
        return -1;

    strncpy(path, dirpath, strlen(dirpath) + 1);
    while ((entry = readdir(dirp)) != NULL) {
        sysapi_file_type type;
        if (entry->d_type == DT_REG)
            type = SYSAPI_FILE_TYPE_REGFILE;
        if (entry->d_type == DT_DIR)
            type = SYSAPI_FILE_TYPE_DIRECT;
        if (type == SYSAPI_FILE_TYPE_REGFILE ||
            type == SYSAPI_FILE_TYPE_DIRECT) {
            strncat(path, entry->d_name, strlen(entry->d_name));
            callback(path, type, app_ctx);
        }
    }

    closedir(dirp);
    return 0;
}

