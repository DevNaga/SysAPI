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

void sysapi_cirque_add(void *libctx, void *data)
{
    struct _sysapi_cirque *queue = libctx;
    struct queue_buf *buf = queue->head;

    while (buf) {
        if (is_free_queue(buf)) {
            buf->data = data;
            buf->allocated = 1;
            break;
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
}

