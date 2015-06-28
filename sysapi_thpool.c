#include "sysapi_thpool.h"

struct worker_queue {
    pthread_t tid;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    void (*func)(void *priv);
    int done;
    void *priv;
    struct worker_queue *next;
};

struct work {
    struct worker_queue *queue_head, *queue_tail;
    struct work *next;
};

static void *__sapi_worker_thread(void *work)
{
    struct worker_queue *mywork = work;
    
    for (; mywork; mywork = mywork->next) {
        pthread_mutex_lock(&mywork->mutex);
        pthread_cond_wait(&mywork->cond, &mywork->mutex);
        if (!mywork->done) {
            mywork->func(mywork->priv);
            mywork->done = 1;
        }
        pthread_mutex_unlock(&mywork->mutex);
    }
    
    return NULL;
}

void *sapi_worker_create(void (*func)(void *priv), void *usr_priv)
{
    struct work *work;
    struct worker_queue *queue;
    
    work = calloc(1, sizeof(struct work));
    if (!work) {
        return NULL;
    }
    
    queue = calloc(1, sizeof(struct worker_queue));
    if (!queue) {
        free(work);
        return NULL;
    }
    
    queue->priv = usr_priv;
    queue->func = func;
    queue->done = 0;
    queue->next = NULL;
    
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
    
    if (!work->queue_head) {
        work->queue_head = queue;
    } else {
        work->queue_tail->next = queue;
        work->queue_tail = queue;
    }
    
    int ret;
    ret = pthread_create(&queue->tid, NULL, __sapi_worker_thread, queue);
    if (ret < 0) {
        free(work);
        free(queue);
        return NULL;
    }
    
    return work;
}

int sapi_queue_work(void *work_priv, void (*func)(void *priv), void *usr_priv)
{
    struct work *work = work_priv;
    struct worker_queue *queue;

    queue = calloc(1, sizeof(struct worker_queue));
    if (!queue) {
        return -1;
    }

    queue->done = 0;
    queue->priv = usr_priv;
    queue->func = func;
    queue->next = NULL;

    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);

    if (!work->queue_head) {
        work->queue_head = queue;
    } else {
        work->queue_tail->next = queue;
        work->queue_tail = queue;
    }

    int ret;

    ret = pthread_create(&queue->tid, NULL, __sapi_worker_thread, queue);
    if (ret < 0) {
        free(queue);
        return -1;
    }

    return 0;
}
