#ifndef __SYSAPI_GC_H__
#define __SYSAPI_GC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define SAPI_MALLOC(ref, len) sapi_malloc(ref, len, __func__, __LINE__)
#define SAPI_CALLOC(ref, len) sapi_calloc(ref, len, __func__, __LINE__)

#define SAPI_SCOPED_MALLOC(ref, len) sapi_scoped_malloc(ref, len, __func__, __LINE__)
#define SAPI_SCOPED_CALLOC(ref, len) sapi_scoped_calloc(ref, len, __func__, __LINE__)

#endif
