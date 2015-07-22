#include "sysapi_process.h"

int sysapi_daemonize(char *wd, char *lfile)
{
    int pid;

    pid = fork();
    if (pid < 0)
        return -1;
    else if (pid > 0)
        exit(0);

    setsid();

    chdir(wd);

    int fd, _fd;

    fd = open("/dev/null", O_RDWR);
    if (fd != 0) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);

        if (fd > 2)
            close(fd);
    }

    umask(027);

    if (lfile) {
        _fd = open(lfile, O_RDWR | O_CREAT);
        if (_fd < 0)
            return -1;

        if (lockf(_fd, F_TLOCK, 0) < 0)
            return -1;
    }
    return 0;
}

