#include "sysapi_cirque.h"

struct queue_buf {
    void *data;
    int allocated;
    struct queue_buf *next;
};

struct _sysapi_cirque {
    int len;
    struct queue_buf *head, *tail;
};

#ifdef LIBSYSAPI_DEBUG
void sysapi_cirque_display(void *queue)
{
    struct _sysapi_cirque *_cirque = queue;
    struct queue_buf *_q = _cirque->head;
    int i = 0;

    printf("\n================ LIST STARTS ==================\n");
    for (_q; _q; _q = _q->next) {
        if (i != 0) {
            if (i % 16 == 0)
                printf("\n");

            printf("%d[%s] ", i, (_q->allocated == 0) ? "-": "x");
        }
        i++;
    }
    printf("\n================ LIST ENDS =====================\n");
}
#endif

static int is_free_queue(struct queue_buf *queue)
{
    return (queue->allocated == 0);
}

void* sysapi_cirque_init(int queues)
{
    struct _sysapi_cirque *queue;
    int i;

    queue = calloc(1, sizeof(struct _sysapi_cirque));
    if (!queue)
        return NULL;

    queue->len = queues;

    for (i = 0; i < queues; i++) {
        struct queue_buf *buf;

        buf = calloc(1, sizeof(struct queue_buf));
        if (!buf)
            goto err_queue_alloc;

        buf->allocated = 0;

        if (i == 0) {
            queue->head = queue->tail = buf;
        } else {
            queue->tail->next = buf;
            queue->tail = buf;
        }
    }

    return queue;

err_queue_alloc:
    free(queue);

    queue = NULL;
    return queue;
}

void* sysapi_cirque_resize(int newqueue, void *libctx)
{
    struct _sysapi_cirque *queue = libctx;
    int new_qlen = 0;
    int i;

    new_qlen = newqueue - queue->len;
    if (new_qlen <= 0)
        return queue;

    for (i = 0; i < new_qlen; i++) {
        struct queue_buf *t = calloc(1, sizeof(struct queue_buf));

        if (!t)
            return queue;

        t->allocated = 0;

        queue->tail->next = t;
        queue->tail = t;
    }
    
    queue->len += new_qlen;

    return queue;
}

int sysapi_get_qlen(void *libctx)
{
    struct _sysapi_cirque *queue = libctx;

    return queue->len;
}

int sysapi_get_empty_qlen(void *libctx)
{
    struct _sysapi_cirque *queue = libctx;

    struct queue_buf *buf = queue->head;
    int count = 0;

    for (buf; buf; buf = buf->next) {
        if (buf->allocated == 0)
            count++;
    }

    return count;
}

void sysapi_cirque_add(void *libctx, void *data)
{
    struct _sysapi_cirque *queue = libctx;
    struct queue_buf *buf = queue->head;

    while (buf) {
        if (is_free_queue(buf)) {
            buf->data = data;
            buf->allocated = 1;
            return;
        }
        buf = buf->next;
    }

    // delete the head of the queue
    // , point to new data and add it at the tail
    queue->head->data = data;
    queue->head->allocated = 1;
    queue->tail->next = queue->head;
    queue->tail = queue->head;
    queue->head = queue->head->next;
    queue->tail->next = NULL;
}

void sysapi_cirque_for_each(void *libctx, void *cbdata, void (*cb_caller)(void *cbdata, void *data))
{
    struct _sysapi_cirque *queue = libctx;
    struct queue_buf *buf = queue->head;

    while (buf) {
        if (buf->allocated)
            cb_caller(cbdata, buf->data);
        buf = buf->next;
    }
}

int sysapi_cirque_mark_node_empty(void *libctx, void *data)
{
    struct _sysapi_cirque *queue = libctx;
    struct queue_buf *buf = queue->head;

    while (buf) {
        if (buf->allocated)
            if (buf->data == data) {
                buf->allocated = 0;
                return 0;
            }
        buf = buf->next;
    }

    return -1;
}

void sysapi_cirque_deinit(void *libctx)
{
    struct _sysapi_cirque *queue = libctx;
    struct queue_buf *buf = queue->head;
    struct queue_buf *prev_buf;

    while (buf) {
        prev_buf = buf;
        buf = buf->next;
        free(prev_buf);
    }

    free(queue);
}

