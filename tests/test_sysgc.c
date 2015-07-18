#include "../core/sysapi_gc.h"

void *reference;

// double allocations overwriting the previous allocation test
void scoped_allocator(int loops, int size)
{
    void *var;

    var = SAPI_SCOPED_MALLOC(reference, size);
    var = SAPI_SCOPED_CALLOC(reference, size);

    sapi_gc_cleanup_scope(reference);
}
void allocator(int loops, int size)
{
    int i;
    void *mem;

    for (i = 0; i < loops; i++) {
        mem = SAPI_MALLOC(reference, size);
        printf("allocated %p %d\n", mem, loops);
        //looped allocation tests
    }
    loops--;
    if (loops <= 0)
        return;
    //allocator(loops, 20);
}
int main(void) {
    reference = sapi_gc_startup();
    scoped_allocator(200, 20);
    allocator(200, 20);
    sapi_gc_cleanup(reference);
    return 0;
}
