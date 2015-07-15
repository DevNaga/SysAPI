#include "sysapi_queue.h"

struct sysapi_queue {
    void *data;
    struct sysapi_queue *next;
};

struct sysapi_queue_head {
    struct sysapi_queue *head;
    struct sysapi_queue *last;
};

void *sysapi_queue_init()
{
    struct sysapi_queue_head *qhead;
    
    qhead = calloc(1, sizeof(struct sysapi_queue_head));
    if (!qhead)
        return NULL;
    
    return qhead;
}

int sysapi_queue_enque(void *data, void *qptr)
{
    struct sysapi_queue_head *qhead = qptr;
    struct sysapi_queue *elem;
    
    elem = calloc(1, sizeof(struct sysapi_queue));
    if (!elem)
        return -1;
    
    elem->data = data;
    if (!qhead->head) {
        qhead->head = elem;
        qhead->last = elem;
    } else {
        qhead->last->next = elem;
        qhead->last = elem;
    }
    
    return 0;
}

int sysapi_queue_deque(void (*cbfunc(void *elem, void *magic)),
                         void *magic,
                         void *qptr)
{
    struct sysapi_queue_head *qhead = qptr;
    struct sysapi_queue *elem;
    
    elem = qhead->head;
    if (!elem)
        return -1;
    
    cbfunc(elem->data, magic);
    qhead->head = elem->next;
    free(elem);
    
    return 0;
}

void sysapi_queue_deinit(void (*freefunc)(void *elem, void *magic),
                        void *magic,
                        void *qptr)
{
    struct sysapi_queue_head *qhead = qptr;
    struct sysapi_queue *elem, *prev;
    
    elem = qhead->head;
    prev = elem;
    
    while (elem) {
        freefunc(elem->data, magic);
        elem = elem->next;
        free(prev);
        prev = elem;
    }
    free(qhead);
}
