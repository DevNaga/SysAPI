#ifndef __SYSAPI_UTIL_H__
#define __SYSAPI_UTIL_H__
#include <stdio.h>
#include <stdarg.h>

#define SYSAPI_LEVEL_INFO 3
#define SYSAPI_LEVEL_WARN 2
#define SYSAPI_LEVEL_ERR  1

#define sysapi_log_info(msg, ...) sysapi_printf(SYSAPI_LEVEL_INFO, msg " "__VA_ARGS__)
#define sysapi_log_warn(msg, ...) sysapi_printf(SYSAPI_LEVEL_WARN, msg " "__VA_ARGS__)
#define sysapi_log_err(msg, ...) sysapi_printf(SYSAPI_LEVEL_ERR, msg " " __VA_ARGS__)

#endif

