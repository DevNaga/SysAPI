#include "sysapi_hashtbl.h"
#include "sysapi_util.h"
#include "sysapi_libgen.h"

#define MAX_HASHES 200

struct list {
    void *data;
    char *name;
    uint32_t hashindx;
    struct list *next;
};

struct hash_table {
    int size;
    struct list **list;
};

void *sapi_hashtbl_init(int size)
{
    if (size < 1) {
        sysapi_err("%s: %s:%u  Invalid hashtable size %d\n",
                __FILE__, __func__, __LINE__, size);
        return NULL;
    }

    struct hash_table *tbl;

    tbl = calloc(1, sizeof(struct hash_table));
    if (!tbl) {
        sysapi_alloc_err();
        return NULL;
    }

    tbl->size = size;

    tbl->list = calloc(tbl->size, sizeof(struct list));
    if (!tbl->list) {
        sysapi_alloc_err();
        goto err_tbl_aloc;
    }

    return tbl;

err_tbl_aloc:
    free(tbl);
    return NULL;
}

int sysapi_get_hashtbl_size(void *ctx)
{
    struct hash_table *tbl = ctx;

    return tbl->size;
}

void sapi_hashtbl_deinit(void *ctx,
                         void (*freefunc)(void *app_ctx, void *data),
                         void *app_ctx)
{
    struct hash_table *hashtbl = ctx;
    struct list *list, *prev;
    int i;

    for (i = 0; i < hashtbl->size; i++) {
        list = hashtbl->list[i];
        prev = list;
        while (list) {
            prev = list->next;
            freefunc(app_ctx, list->data);
            free(list);
            list = prev;
        }
    }
}

unsigned int sapi_hash(void *ctx, char *name)
{
    unsigned int hash = 0;
    struct hash_table *hashtbl = ctx;

    while (*name++)
        hash = *name + (hash << 5) - hash;

    return hash % hashtbl->size;
}

struct list* sapi_find_helem(void *ctx, char *name)
{
    struct hash_table *hashtbl = ctx;
    struct list *elem;
    unsigned int hash = sapi_hash(ctx, name);

    for (elem = hashtbl->list[hash]; elem; elem = elem->next) {
        if (strcmp(elem->name, name) == 0) {
            return elem;
        }
    }

    return NULL;
}

void *sapi_get_helem(void *ctx, char *name)
{
    struct list *item = sapi_find_helem(ctx, name);

    return item->data;
}

void sapi_delete_hlist(void *ctx,
                       void (*freefunc)(void *app_ctx, void *data),
                       void *app_ctx)
{
    struct hash_table *hashtbl = ctx;
    struct list *item, *prev;
    int i;

    for (i = 0; i < hashtbl->size; i++) {
        item = hashtbl->list[i];
        while (item) {
            prev = item->next;
            freefunc(app_ctx, item->data);
            free(item);
            item = prev;
        }
    }
}

void sapi_elem_for_each(void *ctx,
                         void (*usrcb)(void *app_ctx, void *data),
                         void *app_ctx)
{
    struct hash_table *hashtbl = ctx;
    struct list *item;
    int i;

    for (i = 0; i < hashtbl->size; i++) {
        item = hashtbl->list[i];
        while (item) {
            usrcb(app_ctx, item->data);
            item = item->next;
        }
    }
}

int sapi_add_helem(void *ctx, void *data, char *name)
{
    struct hash_table *hashtbl = ctx;
    unsigned int hash_val = sapi_hash(ctx, name);
    struct list *t;

    t = sapi_find_helem(ctx, name);
    if (t)
        return -1;

    t = calloc(1, sizeof(struct list));
    if (!t)
        return -1;

    t->name = strdup(name);
    t->data = data;
    t->hashindx = hash_val;

    t->next = hashtbl->list[hash_val];
    hashtbl->list[hash_val] = t;

    return 0;
}

