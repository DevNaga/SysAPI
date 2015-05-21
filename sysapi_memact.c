#include <stdio.h>
#include <stdlib.h>

struct sysapi_memact_data {
    int memory_limit;
    int memory_len;
};

void *sapi_memact_init(int memory_limit)
{
    struct sysapi_memact_data *memact;

    memact = calloc(1, sizeof(struct sysapi_memact_data));
    if (!memact)
        return memact;

    memact->memory_limit = memory_limit;

    return core;
}

void *sapi_memact_alloc(void *cb, int size)
{
    struct sysapi_memact_data *memact = cb;

    if (memact->memory_len + size >= memact->memory_limit)
        return NULL;

    memact->memory_len += size;

    return calloc(1, size);
}

void sapi_memact_expand(void *cb, int exp_len)
{
    struct sysapi_memact_data *memact = cb;

    memact->memory_limit += exp_len;
}

void sapi_memact_deinit(void *cb)
{
    free(cb);
}
