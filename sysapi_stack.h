#ifndef __SYSAPI_STACK_H__
#define __SYSAPI_STACK_H__

#include <stdio.h>
#include <stdlib.h>


void *sysapi_stack_init();

int sysapi_stack_push(void *elem, void *sptr);

int sysapi_stack_pop(void (*cbfunc)(void *elem, void *magic),
                     void *magic,
                     void *sptr);

void sysapi_stack_deinit(void (*freefunc)(void *elem, void *magic),
                         void *magic,
                         void *sptr);



#endif
