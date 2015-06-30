#include "sysapi_list.h"
#include "sysapi_util.h"
#include "sysapi_gc.h"

struct _gc_mem_identifer {
    int line;
    const char *func;
    bool scoped;
    void *memory;
};

struct _gc_struct {
    void *gc_list;
    void *gc_scoped_list;
};

void *_sapi_alloc(void *__ref, int clear, int scoped, int size, const char *func, int line)
{
    struct _gc_struct *ctx = __ref;

    struct _gc_mem_identifer *ref;

    ref = calloc(1, sizeof(struct _gc_mem_identifer));
    if (!ref)
        return NULL;

    ref->func = func;
    ref->line = line;
    if (clear)
        ref->memory = calloc(1, size);
    else
        ref->memory = malloc(size);

    ref->scoped = scoped;

    if (scoped)
        sapi_list_add_tail(ctx->gc_scoped_list, ref);
    else
        sapi_list_add_tail(ctx->gc_list, ref);

    return ref->memory;
}

void *sapi_malloc(void *__ref, int size, const char *func, int line)
{
    return _sapi_alloc(__ref, false, false, size, func, line);
}

void *sapi_calloc(void *__ref, int size, const char *func, int line)
{
    return _sapi_alloc(__ref, true, false, size, func, line);
}

void *sapi_scope_init(void *__ref)
{
    struct _gc_struct *ref = __ref;

    if (!ref->gc_scoped_list) {
        ref->gc_scoped_list = sapi_list_init();
        if (!ref->gc_scoped_list)
            return NULL;
    }

    return ref;
}

void *sapi_scoped_malloc(void *__ref, int size, const char *func, int line)
{
    sapi_scope_init(__ref);

    return _sapi_alloc(__ref, false, true, size, func, line);
}

void *sapi_scoped_calloc(void *__ref, int size, const char *func, int line)
{
    sapi_scope_init(__ref);

    return _sapi_alloc(__ref, true, true, size, func, line);
}

int _sapi_gc_dump_scoped_heap(void *ref, void *data)
{
    struct _gc_mem_identifer *id = data;

#ifdef SAPI_GC_DEBUG
    static int i;
    sysapi_log_info("SAPIGC:", "freeing memory allocated at %s %u %d\n", id->func, id->line, i++);
#endif
    if (id->scoped) {
        free(id->memory);
        free(id);
    }

    return 0;
}

void sapi_gc_cleanup_scope(void *__ref)
{
    struct _gc_struct *ref = __ref;

    sapi_list_deinit(ref->gc_scoped_list, ref, _sapi_gc_dump_scoped_heap);
    ref->gc_scoped_list = NULL;
}

void *sapi_gc_startup()
{
    struct _gc_struct *ref;

    ref = calloc(1, sizeof(struct _gc_struct));
    if (!ref)
        return NULL;

    ref->gc_list = sapi_list_init();
    if (!ref->gc_list)
        return NULL;

    return ref;
}

int _sapi_gc_dump_heap(void *ref, void *data)
{
    struct _gc_mem_identifer *id = data;

#ifdef SAPI_GC_DEBUG
    static int i;
    sysapi_log_info("SAPIGC:", "freeing memory allocated at %s %u %d\n", id->func, id->line, i++);
#endif

    if (!id->scoped) {
        free(id->memory);
        free(id);
    }
    return 0;
}

void sapi_gc_cleanup(void *__ref)
{
    struct _gc_struct *ref = __ref;

    sapi_list_deinit(ref->gc_list, ref, _sapi_gc_dump_heap);
    free(ref);
}
