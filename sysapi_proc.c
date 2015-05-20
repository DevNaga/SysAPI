#include "sysapi_proc.h"

#define PROC_CMD_LINE "/proc/cmdline"
#define PROC_CMD_LINE_LEN 100

int sysapi_get_kernel_cmdline(char *cmdline)
{
    int fd;

    fd = open(PROC_CMD_LINE, O_RDONLY);
    if (fd < 0)
        return -1;

    read(fd, cmdline, PROC_CMD_LINE_LEN);

    close(fd);

    return 0;
}

#ifdef CONFIG_SYSAPI_PROC_TEST
int main(void)
{
    char cmdline[200];

    int ret;

    ret = sysapi_get_kernel_cmdline(cmdline);

    printf("cmd line %s\n", cmdline);

    return ret;
}
#endif

