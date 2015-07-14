#ifndef __SYSAPI_LIST_H__
#define __SYSAPI_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct sapi_list {
    void *data;
    struct sapi_list *next;
};

struct sapi_list_ctx;

void *sapi_list_init(void);

int sapi_list_add_tail(void *ctx, void *data);

int sapi_list_get_data_iter(void *ctx, void *data, int (*iter_func)(void *ctx, void *, void *));

void* sapi_list_get_next_data(void *ctx);

int sapi_list_delete(void *ctx, int (*delete)(void *, void *), void *data);

int sapi_list_deinit(void *ctx, void *magic, int (*freefunc)(void *, void *));

void *sapi_list_first_elem(void *ctx);

void *sapi_list_last_elem(void *ctx);

int sapi_list_compare_delete(void *ctx, void *data,
                             int (*compare)(void *, void *, void *));

struct sapi_list *sapi_list_get_head(void *ctx);

struct sapi_list *sapi_list_get_tail(void *ctx);

#define sapi_list_item_data(__list) (__list->data)

#define sapi_list_foreach(__ctx, __iter)                           \
    __iter = sapi_list_get_head(__ctx);                            \
    for (__iter; __iter; __iter = __iter->next)                    \

#endif
