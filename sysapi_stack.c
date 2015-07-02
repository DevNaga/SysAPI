#include "sysapi_stack.h"

struct sysapi_stack {
    void *data;
    struct sysapi_stack *next;
};

struct sysapi_stack_head {
    struct sysapi_stack *head, *last;
};

void *sysapi_stack_init()
{
    struct sysapi_stack *shead;
    
    shead = calloc(1, sizeof(struct sysapi_stack));
    if (!shead)
        return NULL;
    
    return shead;
}

int sysapi_stack_push(void *elem, void *sptr)
{
    struct sysapi_stack_head *shead = sptr;
    struct sysapi_stack *stack;
    
    stack = calloc(1, sizeof(struct sysapi_stack));
    if (!stack)
        return -1;
    
    stack->data = elem;
    
    if (!shead->head) {
        shead->head = stack;
        shead->last = stack;
    } else {
        shead->last->next = stack;
        shead->last = stack;
    }
    
    return 0;
}

int sysapi_stack_pop(void (*cbfunc)(void *elem, void *magic),
                     void *magic,
                     void *sptr)
{
    struct sysapi_stack_head *shead = sptr;
    struct sysapi_stack *stack;
    
    stack = shead->head;
    
    if (!stack)
        return -1;
    
    cbfunc(stack->data, magic);
    shead->head = stack->next;
    free(stack);
    
    return 0;
}

void sysapi_stack_deinit(void (*freefunc)(void *elem, void *magic),
                         void *magic,
                         void *sptr)
{
    struct sysapi_stack_head *shead = sptr;
    struct sysapi_stack *stack, *prev_stack;
    
    stack = shead->head;
    prev_stack = stack;
    
    while (stack) {
        freefunc(stack->data, magic);
        stack = stack->next;
        free(prev_stack);
        prev_stack = stack;
    }

    free(shead);
}
