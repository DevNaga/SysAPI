#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "sysapi_fs.h"
#include "sysapi_util.h"

#define ANSI_COLOR_RED     "\x1B[31m"
#define ANSI_COLOR_GREEN   "\x1B[32m"
#define ANSI_COLOR_YELLOW  "\x1B[33m"
#define ANSI_COLOR_BLUE    "\x1B[34m"
#define ANSI_COLOR_MAGENTA "\x1B[35m"
#define ANSI_COLOR_CYAN    "\x1B[36m"
#define ANSI_COLOR_RESET   "\033[0m"

static void sysapi_print_in_red(char *msg, va_list ap)
{
    char str[1024];
    int len;

    len = snprintf(str, sizeof(str), "[ERR:   ] ");
    vsnprintf(str + len, sizeof(str) - len, msg, ap);
    fprintf(stderr, ANSI_COLOR_RED"%s"ANSI_COLOR_RESET, str);
}

static void sysapi_print_in_yellow(char *msg, va_list ap)
{
    char str[1024];
    int len;

    len = snprintf(str, sizeof(str), "[WARN:  ] ");
    vsnprintf(str + len, sizeof(str) - len, msg, ap);
    fprintf(stdout, ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET, str);
}

static void sysapi_print_in_green(char *msg, va_list ap)
{
    char str[1024];
    int len;

    len = snprintf(str, sizeof(str), "[INFO:  ] ");
    vsnprintf(str + len, sizeof(str) - len, msg, ap);
    fprintf(stdout, ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET, str);
}

static void sysapi_print_in_norm(char *msg, va_list ap)
{
    char str[1024];
    int len;

    len = snprintf(str, sizeof(str), "[INFO:  ] ");
    vsnprintf(str + len, sizeof(str) - len, msg, ap);
    fprintf(stdout, "%s", str);
}

void sysapi_printf(int level, char *msg, ...)
{
    va_list ap;
    struct level_printer {
        int level;
        void (*printer)(char *msg, va_list ap);
    } printers[] = {
        {SYSAPI_LEVEL_ERR,  sysapi_print_in_red},
        {SYSAPI_LEVEL_WARN, sysapi_print_in_yellow},
        {SYSAPI_LEVEL_INFO, sysapi_print_in_green},
        {SYSAPI_LEVEL_NORM, sysapi_print_in_norm},
    };
    int level_printer_size = sizeof(printers) / sizeof(printers[0]);

    va_start(ap, msg);

    if (level < 0 || level > level_printer_size)
        level = SYSAPI_LEVEL_NORM + 1;

    printers[level - 1].printer(msg, ap);

    va_end(ap);
}

int sysapi_get_line(char *buf, FILE *fp, int len)
{
    int i = 0;
    int a;

    while (i < len - 1) {
        a = fgetc(fp);
        if ((a == '\n') ||
            (a == EOF)) {
            buf[i] = '\0';
            break;
        }
        buf[i] = a;
        i++;
    }

    return i;
}

int sysapi_get_arch(void)
{
    if ((size_t)-1 > 0xffffffffUL)
        return SYSAPI_ARCH_64_BIT;
    else
        return SYSAPI_ARCH_32_BIT;
}

int sysapi_stringrand(char *elem, int len)
{
    char alphabets[] = {
        'a', 'A',
        'b', 'B',
        'c', 'C',
        'd', 'D',
        'e', 'E',
        'f', 'F',
        'g', 'G',
        'h', 'H',
        'i', 'I',
        'j', 'J',
        'k', 'K',
        'l', 'L',
        'm', 'M',
        'n', 'N',
        'o', 'O',
        'p', 'P',
        'q', 'Q',
        'r', 'R',
        's', 'S',
        't', 'T',
        'u', 'U',
        'v', 'V',
        'w', 'W',
        'x', 'X',
        'y', 'Y',
        'z', 'Z',
    };
    int i;
    int seed;
    struct timeval tv;
    int size_alphabets = sizeof(alphabets) / sizeof(alphabets[0]);

    gettimeofday(&tv, 0);
    seed = tv.tv_usec;

    srand(seed);

    for (i = 0; i < len - 1; i++)
        elem[i] = alphabets[rand() % size_alphabets];

    elem[i] = '\0';

    return 0;
}

int sysapi_get_rand(void)
{
    int fd;
    int ret;
    int number = 0;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0)
        return -1;

    ret = read(fd, &number, sizeof(number));
    if (ret < 0) {
        close(ret);
        return -1;
    }

    return number;
}

int sysapi_get_rand_range(int range)
{
    int ret;

    ret = sysapi_get_rand();
    if (ret != -1) {
        if (ret < 0)
            ret *= -1;
        return ret % range;
    }

    return ret;
}

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

    _fd = open(lfile, O_RDWR | O_CREAT);
    if (_fd < 0)
        return -1;

    if (lockf(_fd, F_TLOCK, 0) < 0)
        return -1;
    return 0;
}

int sysapi_create_lockfile(char *lfile)
{
    int fd;

    fd = open(lfile, O_RDWR | O_CREAT);
    if (lockf(fd, F_TLOCK, 0) < 0)
        return -1;
    return 0;
}

int sysapi_device_isatty(int fd)
{
    return isatty(fd);
}

int sysapi_get_ttyname(int fd, char *name, int len)
{
    return ttyname_r(fd, name, len);
}

int sapi_strvjoin(char *result, int result_len, char *delimiter, int n_strings, ...)
{
    va_list ap;
    int len = 0;
    int off = 0;
    int i;

    va_start(ap, n_strings);

    for (i = 0; i < n_strings; i++) {
        char *_item = va_arg(ap, char *);
        if (_item) {
            len = snprintf(result + off, result_len, "%s", _item);
            off += len;
            if (delimiter) {
                len = snprintf(result + off, result_len, "%s", delimiter);
                off += len;
            }
        }
    }

    va_end(ap);
    
    return off;
}

int sysapi_strempty(char *string)
{
    return string ? (string[0] == "" ? 1: 0): 1;
}

char *sysapi_strrev(char *string, char *reverse, int rev_len)
{
    int len = strlen(string);
    int i, j;

    for (i = len, j = 0; i > 0, j < rev_len; i--, j++)
        reverse[j] = string[i];

    reverse[j] = '\0';
    return reverse;
}

struct _sysapi_internal_file_ext {
    char *filext;
    int found;
    void (*callback)(char *filename);
};

static void _sysapi_file_checker(char *filename,
                          sysapi_file_type ftype,
                          void *ctx)
{
    struct _sysapi_internal_file_ext *__fext = ctx;
    int result = 0;
    char *end;
    char ext[30] = {};
    char ext_new[30] = {};
    int i = 0;

    if (ftype == SYSAPI_FILE_TYPE_REGFILE) {
        end = filename + strlen(filename);
        while ((*end != '.') && (i < sizeof(ext))) {
            ext[i] = *end;
            end++;
            i++;
        }

        ext[i] = '\0';
        sysapi_strrev(ext, ext_new, sizeof(ext_new));

        if (strcmp(ext_new, __fext->filext) == 0) {
            __fext->found = 1;
            __fext->callback(filename);
        }
    }
}

int sysapi_find_files_with_ext(char *dir, char *ext,
                               void (*callback)(char *filename))
{
    struct _sysapi_internal_file_ext *_fext;
    int ret;

    _fext = calloc(1, sizeof(struct _sysapi_internal_file_ext));
    if (!_fext)
        return -1;

    _fext->found = 0;
    _fext->filext = ext;
    _fext->callback = callback;

    ret = sysapi_dir_read(dir, _sysapi_file_checker, _fext);
    if (!ret) {
        if (_fext->found)
            ret = 0;
        else
            ret = -1;
    }

    return ret;
}

void sysapi_skip_line(FILE *fp)
{
    while (fgetc(fp) != '\n');
}
