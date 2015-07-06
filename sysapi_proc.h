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
#include "sysapi_libgen.h"

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

struct sysapi_crypto_avail {
	int name:1;
	int driver:1;
	int module:1;
	int priority:1;
	int refcnt:1;
	int selftest:1;
	int type:1;
	int seedsize:1;
	int blocksize:1;
	int digestsize:1;
	int min_keysize:1;
	int max_keysize:1;
} __attribute__((__packed__));

#define SYSAPI_CRYPTO_BUFLEN 20

struct sysapi_sys_crypto_info {
	char name[SYSAPI_CRYPTO_BUFLEN];
	char driver[SYSAPI_CRYPTO_BUFLEN];
	char module[SYSAPI_CRYPTO_BUFLEN];
	int priority;
	int refcnt;
	char selftest[SYSAPI_CRYPTO_BUFLEN];
	char type[SYSAPI_CRYPTO_BUFLEN];
	int seedsize;
	int blocksize;
	int digestsize;
	int min_keysize;
	int max_keysize;
	struct sysapi_crypto_avail avail;
	struct sysapi_sys_crypto_info *next;
};

int sysapi_get_kernel_cmdline(char *cmdline);

int sysapi_proc_get_hostname(char *hostname, int len);

int sysapi_proc_set_hostname(char *hostname, int len);

int sysapi_get_kernel_release(char *release, int len);

int sysapi_get_kernel_meminfo(struct sysapi_kernel_meminfo *meminfo);

#endif

