#ifndef __SYSAPI_HASHTBL_H__
#define __SYSAPI_HASHTBL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void *sapi_hashtbl_init(int tbl_len);

void sapi_hashtbl_deinit(void *handle,
                             void (*freefunc)(void *app_ctx, void *data),
                             void *app_cb);
                             
unsigned int sapi_hash(void *ctx, char *name);

struct list* sapi_find_helem(void *ctx, char *name);

void *sapi_get_helem(void *ctx, char *name);

void *sapi_get_elem(void *ctx, char *name);

void sapi_delete_hlist(void *handle,
                             void (*freefunc)(void *app_ctx, void *data),
                             void *app_cb);
                             
void sapi_elem_for_each(void *handle,
                             void (*usrcb)(void *app_ctx, void *data),
                             void *app_cb);
                             
int sapi_add_helem(void *ctx, void *data, char *name);

#endif
