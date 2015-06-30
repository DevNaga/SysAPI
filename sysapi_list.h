#ifndef __SYSAPI_LIST_H__
#define __SYSAPI_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void *sapi_list_init(void);

int sapi_list_add_tail(void *ctx, void *data);

int sapi_list_get_data_iter(void *ctx, int (*iter_func)(void *ctx, void *data));

void* sapi_list_get_next_data(void *ctx);

int sapi_list_delete(void *ctx, int (*delete)(void *, void *), void *data);

int sapi_list_deinit(void *ctx, void *magic, int (*freefunc)(void *, void *));

#endif
