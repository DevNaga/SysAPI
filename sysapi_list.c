#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct sapi_list {
    void *data;
    struct sapi_list *next;
};

struct sapi_list_ctx {
    int n_items;
    struct sapi_list *next_iter;
    struct sapi_list *head, *tail;
};

void *sapi_list_init(void)
{
    struct sapi_list_ctx *ctx;

    ctx = calloc(1, sizeof(struct sapi_list_ctx));
    if (!ctx)
        return NULL;

    return ctx;
}

int sapi_list_add_tail(void *ctx, void *data)
{
    int ret;
    struct sapi_list_ctx *list_ctx = ctx;
    struct sapi_list *list;

    ret = -1;
    list = calloc(1, sizeof(struct sapi_list));
    if (!list)
        return ret;

    list->data = data;

    if (!list_ctx->head) {
        list_ctx->head = list;
        list_ctx->tail = list;
        list_ctx->next_iter = list;
    } else {
        list_ctx->tail->next = list;
        list_ctx->tail = list;
    }
    return ret;
}

int sapi_list_get_data_iter(void *ctx, int (*iter_func)(void *ctx, void *data))
{
    int ret;
    struct sapi_list_ctx *list_ctx = ctx;
    struct sapi_list *list;

    ret = -1;
    for (list = list_ctx->head; list; list = list->next) {
        if (iter_func)
            iter_func(list_ctx, list->data);
        else
            printf("missing iterator function\n");
    }

    ret = 0;
    return ret;
}

void* sapi_list_get_next_data(void *ctx)
{
    struct sapi_list_ctx *list_ctx = ctx;
    struct sapi_list *list = list_ctx->next_iter;

    list_ctx->next_iter = list_ctx->next_iter->next;
    return list->data;
}

int sapi_list_delete(void *ctx, int (*delete)(void *, void *), void *data)
{
    int ret;
    struct sapi_list_ctx *list_ctx = ctx;
    struct sapi_list *prev, *cur;

    cur = list_ctx->head;
    prev = cur;

    ret = -1;
    if (cur->data == data) {
        if (list_ctx->tail == cur) {
            list_ctx->tail = NULL;
            list_ctx->head = NULL;
            if (delete)
                delete(list_ctx, cur->data);
            free(cur);
        } else {
            list_ctx->head = cur->next;
            if (delete)
                delete(list_ctx, cur->data);
            free(cur);
        }
        return 0;
    }

    while (cur) {
        if (cur->data == data) {
            prev->next = cur->next;
            delete(list_ctx, cur->data);
            ret = 0;
            break;
        }

        prev = cur;
        cur = cur->next;
    }

    return ret;
}

int sapi_list_deinit(void *ctx, int (*freefunc)(void *, void *))
{
    struct sapi_list_ctx *list_ctx = ctx;
    struct sapi_list *prev, *cur;
    int ret;

    ret = -1;
    cur = list_ctx->head;

    ret = 0;
    while (cur) {
        freefunc(list_ctx, cur->data);
        prev = cur;
        cur = cur->next;
        free(prev);
    }

    return ret;
}

