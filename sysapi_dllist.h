#ifndef __SYSAPI_DLLIST_H__
#define __SYSAPI_DLLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *sysapi_dllist_init(void);

int sysapi_dllist_add(void *data, void *dlptr);

int sysapi_dllist_for_each_forward(void (*cbfunc)(void *data, void *magic),
                                   void *magic,
                                   void *dlptr);

int sysapi_dllist_for_each_reverse(void (*cbfunc)(void *data, void *magic),
                                   void *magic,
                                   void *dlptr);

int sysapi_dllist_remove(void *data, void (*freefunc)(void *data, void *magic),
                         void *magic,
                         void *dlptr);

void sysapi_dllist_deinit_forward(void (*freefunc)(void *data, void *magic),
                                  void *magic,
                                  void *dlptr);

void sysapi_dllist_deinit_reverse(void (*freefunc)(void *data, void *magic),
                                  void *magic,
                                  void *dlptr);

#endif
