

struct sapi_read_evlist {
    pthread_t t;
    struct sapi_read_evlist *next;
};

struct sapi_read_evthread {
    int sock;
    void *priv;
};

struct sapi_event_data {
    fd_set allfd;
    int maxfd;
    struct sapi_read_evlist *head;
    struct sapi_read_evlist *tail;
};

#define SET_THREAD_EVPRIV(__evthread, __libpriv) (__evthread->priv = __livpriv)

int sapi_read_evlist_add(struct sapi_event_data *sapi_evdata, pthread_t tid)
{
    struct sapi_read_evlist *list;

    list = calloc(1, sizeof(*list));
    if (!list)
        return -1;

    list->t = tid;

    if (!sapi_evdata->head) {
        sapi_evdata->head = list;
        sapi_evdata->tail = list;
    } else {
        sapi_evdata->tail->next = list;
        sapi_evdata->tail = list;
    }

    return 0;
}

void *sapi_read_evthreader(void *priv)
{
    struct sapi_read_evthread *thr_ctx = priv;

    for (;;) {
    };
}

int sapi_reg_read_event(int sock, void *libctx, void (*sapi_event_cb)(void *appctx))
{
    struct sapi_event_data *sapi_evdata = libctx;
    pthread_t t;
    struct sapi_read_evthread *new_tctx;

#ifdef CONFIG_NO_THREADS
    FD_SET(sock, &sapi_evdata->allfd);

    if (sock > sapi_evdata->maxfd)
        sapi_evdata->maxfd = sock;
#endif

    new_tctx = calloc(1, sizeof(*new_tctx));
    if (!new_tctx)
        return -1;

    new_tctx->sock = sock;
    SET_THREAD_EVPRIV(new_tctx, sapi_evdata);

    if (pthread_create(&t, NULL, sapi_read_evthreader, new_tctx) < 0)
        goto err_create_thread;

    return 0;

err_create_thread:
    free(new_tctx);
    return -1;
}

