#include "sysapi_list.h"

struct sapi_list_ctx {
    int n_items;
    struct sapi_list *next_iter;
    struct sapi_list *head, *tail;
};

struct sapi_list *sapi_list_get_head(void *ctx)
{
    return ((struct sapi_list_ctx *)ctx)->head;
}

struct sapi_list *sapi_list_get_tail(void *ctx)
{
    return ((struct sapi_list_ctx *)ctx)->tail;
}

void *sapi_list_first_elem(void *ctx)
{
    struct sapi_list_ctx *list_ctx = ctx;

    return list_ctx->head->data;
}

void *sapi_list_last_elem(void *ctx)
{
    struct sapi_list_ctx *list_ctx = ctx;

    return list_ctx->tail->data;
}

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

    ret = 0;
    return ret;
}

int sapi_list_get_data_iter(void *ctx, void *data, int (*iter_func)(void *ctx, void *, void *))
{
    int ret;
    struct sapi_list_ctx *list_ctx = ctx;
    struct sapi_list *list;

    ret = -1;
    for (list = list_ctx->head; list; list = list->next)
        if (iter_func)
            iter_func(list_ctx, data, list->data);

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

int sapi_list_compare_delete(void *ctx, void *data, int (*compare)(void *, void *, void *))
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
            if (compare) {
                ret = compare(list_ctx, data, cur->data);
                if (ret)
                    free(cur);
            }
        } else {
            list_ctx->head = cur->next;
            if (compare) {
                ret = compare(list_ctx, data, cur->data);
                if (ret)
                    free(cur);
            }
        }
        return 0;
    }

    while (cur) {
        if (cur->data == data) {
            prev->next = cur->next;
            if (compare) {
                ret = compare(list_ctx, data, cur->data);
                if (ret)
                    free(cur);
            }
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    return ret;
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
            if (delete)
                delete(list_ctx, cur->data);
            free(cur);
            ret = 0;
            break;
        }

        prev = cur;
        cur = cur->next;
    }

    return ret;
}

int sapi_list_deinit(void *ctx, void *magic, int (*freefunc)(void *, void *))
{
    struct sapi_list_ctx *list_ctx = ctx;
    struct sapi_list *prev, *cur;
    int ret;

    ret = -1;
    cur = list_ctx->head;

    ret = 0;
    while (cur) {
        freefunc(magic, cur->data);
        prev = cur;
        cur = cur->next;
        free(prev);
    }

    free(list_ctx);

    return ret;
}
