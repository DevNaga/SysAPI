
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

static void *_sapi_alloc(void *__ref,
                         int clear,
                         int scoped,
                         int size,
                         const char *func,
                         int line);

static void *sapi_scope_init(void *__ref);

static int _sapi_gc_dump_heap(void *ref, void *data);
