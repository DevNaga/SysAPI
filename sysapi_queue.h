#ifndef __SYSAPI_QUEUE_H__
#define __SYSAPI_QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

void *sysapi_queue_init(void);

int sysapi_queue_enque(void *data, void *qptr);

int sysapi_queue_deque(void (*cbfunc(void *elem, void *magic)),
                       void *magic,
                       void *qptr);

void sysapi_queue_deinit(void (*freefunc)(void *elem, void *magic),
                         void *magic,
                         void *qptr);



#endif
