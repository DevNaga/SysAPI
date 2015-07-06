#ifndef __SAPI_EVENT_H__
#define __SAPI_EVENT_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>
#include <pthread.h>

void *sapi_event_system_init(void);

void sapi_event_system_deinit(void *libctx);

int sapi_reg_read_event(int sock, void *libctx, void *appctx,
                     void (*sapi_read_event_cb)(void *appctx));

void sapi_unreg_read_event(void *libctx, int sock);

void sapi_register_term_signal(void *libctx, void *app_cb,
                               void (*signal_evcb)(void *));

void sapi_event_loop(void *libctx);

#endif
