#include <stdio.h>
#include <stdarg.h>
#include "sysapi_util.h"

#define ANSI_COLOR_RED     "\x1B[31m"
#define ANSI_COLOR_GREEN   "\x1B[32m"
#define ANSI_COLOR_YELLOW  "\x1B[33m"
#define ANSI_COLOR_BLUE    "\x1B[34m"
#define ANSI_COLOR_MAGENTA "\x1B[35m"
#define ANSI_COLOR_CYAN    "\x1B[36m"
#define ANSI_COLOR_RESET   "\033[0m"

void sysapi_print_in_red(char *msg, va_list ap)
{
    char str[1024];
    int len;

    len = snprintf(str, sizeof(str), "[ERR:] ");
    vsnprintf(str + len, sizeof(str) - len, msg, ap);
    fprintf(stderr, ANSI_COLOR_RED"%s"ANSI_COLOR_RESET, str);
}

void sysapi_print_in_yellow(char *msg, va_list ap)
{
    char str[1024];
    int len;

    len = snprintf(str, sizeof(str), "[WARN:] ");
    vsnprintf(str + len, sizeof(str) - len, msg, ap);
    fprintf(stdout, ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET, str);
}

void sysapi_print_in_green(char *msg, va_list ap)
{
    char str[1024];
    int len;

    len = snprintf(str, sizeof(str), "[INFO:] ");
    vsnprintf(str + len, sizeof(str) - len, msg, ap);
    fprintf(stdout, ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET, str);
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
    };

    va_start(ap, msg);

    printers[level - 1].printer(msg, ap);

    va_end(ap);
}

