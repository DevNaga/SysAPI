#ifndef __SYSAPI_THPOOL_H__
#define __SYSAPI_THPOOL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

void *sapi_worker_create(void (*func)(void *priv), void *usr_priv);

int sapi_queue_work(void *work_priv,
		            void (*func)(void *priv), void *usr_priv);

int sapi_start_work_for(void *priv, void (*func)(void *priv));

int sapi_start_work_all(void *priv);

#endif
