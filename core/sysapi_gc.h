#ifndef __SYSAPI_GC_H__
#define __SYSAPI_GC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

void *sapi_gc_startup(void);
void sapi_gc_cleanup(void *__ref);
void *sapi_malloc(void *__ref, int size, const char *func, int line);
void *sapi_calloc(void *__ref, int size, const char *func, int line);

#define SAPI_MALLOC(ref, len) sapi_malloc(ref, len, __func__, __LINE__)
#define SAPI_CALLOC(ref, len) sapi_calloc(ref, len, __func__, __LINE__)

void *sapi_scoped_malloc(void *__ref, int size, const char *func, int line);
void *sapi_scoped_calloc(void *__ref, int size, const char *func, int line);
void sapi_gc_cleanup_scope(void *__ref);

#define SAPI_SCOPED_MALLOC(ref, len) sapi_scoped_malloc(ref, len, __func__, __LINE__)
#define SAPI_SCOPED_CALLOC(ref, len) sapi_scoped_calloc(ref, len, __func__, __LINE__)

#endif
