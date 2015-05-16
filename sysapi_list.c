
struct sapi_list {
    void *data;
    int (*delete_func)(void *data, void *lib_ctx);
    int (*free_func)(void *data, void *lib_ctx);
    int (*sort_func)(void *data, void *lib_ctx);
};

struct sapi_list_ctx {
    int n_items;
    struct sapi_list *head, *tail;
};

void *sapi_list_init(void)
{
    struct sapi_list_ctx *ctx;

    return ctx;
}

int sapi_add_tail(void *ctx, void *data)
{
    int ret;

    return ret;
}

int sapi_insert(void *ctx, void *data)
{
    int ret;

    return ret;
}

int sapi_delete(void *ctx, int (*delete)(void *, void *), void *data)
{
    int ret;

    return ret;
}

int sapi_deinit(void *ctx, int (*free)(void *, void *), void *data)
{
    int ret;

    return ret;
}

