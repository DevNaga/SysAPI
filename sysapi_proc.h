#ifndef __SYSAPI_PROC_H__
#define __SYSAPI_PROC_H__

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

struct sysapi_kernel_meminfo {
	int memtotal;
	int memfree;
	int memavail;
	int buffers;
	int cached;
	int swap_cached;
	int active;
	int inactive;
	int active_anon;
	int inactive_anon;
	int active_file;
	int inactive_file;
	int unevictable;
	int mlocked;
	int swap_total;
	int swap_free;
	int dirty;
	int writeback;
	int anonpages;
	int mapped;
	int shmem;
	int slab;
	int sreclaimable;
	int sunreclaim;
	int kernelstack;
	int pagetables;
	int nfs_unstable;
	int bounce;
	int writebacktmp;
	int commitlimit;
	int commited_as;
	int vmalloctotal;
	int vmallocused;
	int vmallocchunk;
	int hardwarecorrupted;
	int anonhugepages;
	int cmatotal;
	int cmafree;
	int hugepagestotal;
	int hugepagesfree;
	int hugepagesrsvd;
	int hugepagessurp;
	int hugepagesize;
	int directmap4k;
	int directmap2m;
};

#endif

