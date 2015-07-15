#ifndef __SYSAPI_CIRQUE_H__
#define __SYSAPI_CIRQUE_H__

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

void *sysapi_cirque_init(int queues);

void sysapi_cirque_add(void *libctx, void *data);

void sysapi_cirque_for_each(void *libctx, void *cbdata, void (*cb_caller)(void *cbdata, void *data));

int sysapi_cirque_mark_node_empty(void *libctx, void *data);

#define sysapi_cirque_delete_node sysapi_cirque_mark_node_empty

void sysapi_cirque_deinit(void *libctx);

#ifdef LIBSYSAPI_DEBUG

void sysapi_cirque_display(void *libctx);

#else

#define sysapi_cirque_display(libctx) {}

#endif

#endif

