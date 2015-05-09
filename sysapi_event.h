#ifndef __SAPI_EVENT_H__
#define __SAPI_EVENT_H__

void *sapi_event_system_init(void);

void sapi_event_system_deinit(void *libctx);

int sapi_read_evlist_add(struct sapi_event_data *sapi_evdata, pthread_t tid,
                            struct sapi_read_evthread *thrdata);

void *sapi_read_evthreader(void *priv);

int sapi_reg_read_event(int sock, void *libctx, void *appctx,
                     void (*sapi_read_event_cb)(void *appctx));

void sapi_event_loop(void *libctx);

#endif
