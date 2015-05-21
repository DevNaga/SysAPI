#ifndef __SYSAPI_MEMACT_H__
#define __SYSAPI_MEMACT_H__

#include <stdio.h>
#include <stdlib.h>

void *sapi_memact_init(int memory_limit);
void *sapi_memact_alloc(void *cb, int size);
void sapi_memact_expand(void *cb, int exp_len);
void sapi_memact_deinit(void *cb);

#endif
