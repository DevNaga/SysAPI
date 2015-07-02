#include "sysapi_dllist.h"

struct sysapi_dllist {
    void *data;
    struct sysapi_dllist *next;
    struct sysapi_dllist *prev;
};

struct sysapi_dllist_head {
    struct sysapi_dllist *head;
    struct sysapi_dllist *tail;
    int count;
};

void *sysapi_dllist_init(void)
{
    struct sysapi_dllist_head *dlhead;
    
    dlhead = calloc(1, sizeof(struct sysapi_dllist_head));
    if (!dlhead)
        return NULL;
    
    return dlhead;
}

int sysapi_dllist_add(void *data, void *dlptr)
{
    struct sysapi_dllist_head *dlhead = dlptr;
    struct sysapi_dllist *new;

    new = calloc(1, sizeof(struct sysapi_dllist));
    if (!new)
        return -1;

    new->data = data;
    new->prev = new->next = NULL;
    if (!dlhead->head) {
        dlhead->head = new;
        dlhead->tail = new;
    } else {
        new->prev = dlhead->tail;
        new->next = NULL;
        dlhead->tail = new;
    }

    return 0;
}

int sysapi_dllist_for_each_forward(void (*cbfunc)(void *data, void *magic),
                           void *magic,
                           void *dlptr)
{
    struct sysapi_dllist_head *dlhead = dlptr;
    struct sysapi_dllist *iter = dlhead->head;
   
    // we have empty elements in the list
    if (!iter)
        return -1;
    
    while (iter) {
        cbfunc(iter->data, magic);
        iter = iter->next;
    }
    
    return 0;
}

int sysapi_dllist_for_each_reverse(void (*cbfunc)(void *data, void *magic),
                                   void *magic,
                                   void *dlptr)
{
    struct sysapi_dllist_head *dlhead = dlptr;
    struct sysapi_dllist *iter = dlhead->tail;
    
    if (!iter)
        return -1;
    
    while (iter) {
        cbfunc(iter->data, magic);
        iter = iter->prev;
    }
    
    return 0;
}

int sysapi_dllist_remove(void *data, void (*freefunc)(void *data, void *magic),
                         void *magic,
                         void *dlptr)
{
    struct sysapi_dllist_head *dlhead = dlptr;
    struct sysapi_dllist *cur, *prev;
    
    cur = dlhead->head;

    if (!cur)
        return -1;
    
    if (cur->data == data) {
        freefunc(cur->data, magic);
        dlhead->head = cur->next;
        cur->prev = NULL;
        free(cur);
        return 0;
    }
    
    prev = cur;
    while (cur) {
        if (cur->data == data) {
            prev->next = cur->next;
            cur->next->prev = prev;
            freefunc(cur->data, magic);
            free(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    
    return -1;
}

void sysapi_dllist_deinit_forward(void (*freefunc)(void *data, void *magic),
                         void *magic,
                         void *dlptr)
{
    struct sysapi_dllist_head *dlhead = dlptr;
    struct sysapi_dllist *iter = dlhead->head, *prev;
    
    prev = iter;
    while (iter) {
        freefunc(iter->data, magic);
        iter = iter->next;
        free(prev);
        prev = iter;
    }
    
    free(dlhead);
}

void sysapi_dllist_deinit_reverse(void (*freefunc)(void *data, void *magic),
                                  void *magic,
                                  void *dlptr)
{
    struct sysapi_dllist_head *dlhead = dlptr;
    struct sysapi_dllist *iter = dlhead->tail, *prev;
    
    prev = iter;
    while (iter) {
        freefunc(iter->data, magic);
        iter = iter->prev;
        free(prev);
        prev = iter;
    }

    free(dlhead);
}
