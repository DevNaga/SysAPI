#ifndef __SYSAPI_UTIL_H__
#define __SYSAPI_UTIL_H__
#include <stdio.h>
#include <stdarg.h>

#define SYSAPI_LEVEL_NORM 4
#define SYSAPI_LEVEL_INFO 3
#define SYSAPI_LEVEL_WARN 2
#define SYSAPI_LEVEL_ERR  1

// log the informational message
// this will show up green on the console
#define sysapi_log_info(msg, ...) sysapi_printf(SYSAPI_LEVEL_INFO, msg " "__VA_ARGS__)

// log the warning message
// this will show up yellow on the console
#define sysapi_log_warn(msg, ...) sysapi_printf(SYSAPI_LEVEL_WARN, msg " "__VA_ARGS__)

// log the error message
// this will show up red on the console
#define sysapi_log_err(msg, ...) sysapi_printf(SYSAPI_LEVEL_ERR, msg " " __VA_ARGS__)

// log the normal informational message
// this will show up as a normal message on the console
#define sysapi_log_norm(msg, ...) sysapi_printf(SYSAPI_LEVEL_NORM, msg " " __VA_ARGS__)

#endif

