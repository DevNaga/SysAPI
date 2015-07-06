#ifndef __SYSAPI_EVENT_I_H__
#define __SYSAPI_EVENT_I_H__

struct sapi_read_evthread {
    int sock;
    pthread_cond_t read_cond;
    pthread_mutex_t cond_mutex;
    void *app_cb;
    void (*sapi_read_event_cb) (void *);
    void *priv;
};

struct sapi_read_evlist {
    pthread_t t;
    struct sapi_read_evthread *thread_data;
    struct sapi_read_evlist *next;
};

struct sapi_signal_evlist {
    int signal_no;
    void *app_cb;
    void (*sapi_signal_evcallback)(void *app_cb);
    struct sapi_signal_evlist *next;
};

struct sapi_event_data {
    fd_set allfd;
    int maxfd;
    struct sapi_read_evlist *head;
    struct sapi_read_evlist *tail;
    struct sapi_signal_evlist *s_head;
    struct sapi_signal_evlist *s_tail;
};

int sapi_read_evlist_add(struct sapi_event_data *sapi_evdata, pthread_t tid,
                            struct sapi_read_evthread *thrdata);

void *sapi_read_evthreader(void *priv);

int sapi_add_s_elem(int sigmask,
                    struct sapi_event_data *sapi_evdata,
                    void *app_cb, void (*signal_evcb)(void *));

void sapi_deinit_thread(pthread_t t,
                        struct sapi_read_evthread *thr_data);

#endif

