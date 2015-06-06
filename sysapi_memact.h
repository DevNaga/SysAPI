#ifndef __SYSAPI_MEMACT_H__
#define __SYSAPI_MEMACT_H__

#include <stdio.h>
#include <stdlib.h>

// initialise memory accounting module
// memory_limit is the total limit on the
// program's memory usage.
void *sapi_memact_init(int memory_limit);

// use this instead of calling c(m)alloc
// allocation fails, if the memory requested
// will be more than the limit specified at
// the initialisation procedure
void *sapi_memact_alloc(void *cb, int size);

// expand the memory limit on the total program
// allocation
// only call if needed.. 
void sapi_memact_expand(void *cb, int exp_len);

// deinit the memory accounting module
void sapi_memact_deinit(void *cb);

#endif
