#include "sysapi_proc.h"

#define PROC_MEM_INFO "/proc/meminfo"
#define PROC_CMD_LINE "/proc/cmdline"
#define PROC_CMD_LINE_LEN 100

int sysapi_get_kernel_cmdline(char *cmdline)
{
    int fd;

    fd = open(PROC_CMD_LINE, O_RDONLY);
    if (fd < 0)
        return -1;

    read(fd, cmdline, PROC_CMD_LINE_LEN);

    close(fd);

    return 0;
}

int sysapi_get_kernel_meminfo(struct sysapi_kernel_meminfo *meminfo)
{
#define SYSAPI_MEMTOTAL "MemTotal"
#define SYSAPI_MEMFREE "MemFree"
#define SYSAPI_MEMAVAIL "MemAvailable"
#define SYSAPI_BUFFERS "Buffers"
#define SYSAPI_CACHED "Cached"
#define SYSAPI_SWAP_CACHED "SwapCached"
#define SYSAPI_ACTIVE "Active"
#define SYSAPI_INACTIVE "Inactive"
#define SYSAPI_ACTIVE_ANON "Active(anon)"
#define SYSAPI_INACTIVE_ANON "Inactive(anon)"
#define SYSAPI_ACTIVE_FILE "Active(file)"
#define SYSAPI_INACTIVE_FILE "Inactive(file)"
#define SYSAPI_UNEVICTABLE "Unevictable"
#define SYSAPI_MLOCKED "Mlocked"
#define SYSAPI_SWAP_TOTAL "SwapTotal"
#define SYSAPI_SWAP_FREE "SwapFree"
#define SYSAPI_DIRTY "Dirty"
#define SYSAPI_WRITEBACK "Writeback"
#define SYSAPI_ANONPAGES "AnonPages"
#define SYSAPI_MAPPED "Mapped"
#define SYSAPI_SHMEM "Shmem"
#define SYSAPI_SLAB "Slab"
#define SYSAPI_SRECLAIMABLE "SReclaimable"
#define SYSAPI_SUNRECLAIM "SUnreclaim"
#define SYSAPI_KERNEL_STACK "KernelStack"
#define SYSAPI_PAGE_TABLE "PageTables"
#define SYSAPI_NFS_UNSTABLE "NFS_Unstable"
#define SYSAPI_BOUNCE "Bounce"
#define SYSAPI_WRITEBACK_TMP "WritebackTmp"
#define SYSAPI_COMMIT_LIMIT "CommitLimit"
#define SYSAPI_COMMITED_AS "Committed_AS"
#define SYSAPI_VMALLOC_TOTAL "VmallocTotal"
#define SYSAPI_VMALLOC_USED "VmallocUsed"
#define SYSAPI_VMALLOC_CHUNK "VmallocChunk"
#define SYSAPI_HARDWARE_CORRUPTED "HardwareCorrupted"
#define SYSAPI_ANON_HUGE_PAGES "AnonHugePages"
#define SYSAPI_CMA_TOTAL "CmaTotal"
#define SYSAPI_CMA_FREE "CmaFree"
#define SYSAPI_HUGE_PAGES_TOTAL "HugePages_Total"
#define SYSAPI_HUGE_PAGES_FREE "HugePages_Free"
#define SYSAPI_HUGE_PAGES_RSVD "HugePages_Rsvd"
#define SYSAPI_HUGE_PAGES_SURP "HugePages_Surp"
#define SYSAPI_HUGE_PAGE_SIZE "Hugepagesize"
#define SYSAPI_DIRECT_MAP4K "DirectMap4k"
#define SYSAPI_DIRECT_MAP2M "DirectMap2M"

    struct _meminfo_meta {
        char *name;
        int off;
    } _meminfo [] = {
        {SYSAPI_MEMTOTAL, offsetof(struct sysapi_kernel_meminfo, memtotal)},
        {SYSAPI_MEMFREE, offsetof(struct sysapi_kernel_meminfo, memfree)},
        {SYSAPI_MEMAVAIL, offsetof(struct sysapi_kernel_meminfo, memavail)},
        {SYSAPI_BUFFERS, offsetof(struct sysapi_kernel_meminfo, buffers)},
        {SYSAPI_CACHED, offsetof(struct sysapi_kernel_meminfo, cached)},
        {SYSAPI_SWAP_CACHED, offsetof(struct sysapi_kernel_meminfo, swap_cached)},
        {SYSAPI_ACTIVE, offsetof(struct sysapi_kernel_meminfo, active)},
        {SYSAPI_INACTIVE, offsetof(struct sysapi_kernel_meminfo, inactive)},
        {SYSAPI_ACTIVE_ANON, offsetof(struct sysapi_kernel_meminfo, active_anon)},
        {SYSAPI_INACTIVE_ANON, offsetof(struct sysapi_kernel_meminfo, inactive_anon)},
        {SYSAPI_ACTIVE_FILE, offsetof(struct sysapi_kernel_meminfo, active_file)},
        {SYSAPI_INACTIVE_FILE, offsetof(struct sysapi_kernel_meminfo, inactive_file)},
        {SYSAPI_UNEVICTABLE, offsetof(struct sysapi_kernel_meminfo, unevictable)},
        {SYSAPI_MLOCKED, offsetof(struct sysapi_kernel_meminfo, mlocked)},
        {SYSAPI_SWAP_TOTAL, offsetof(struct sysapi_kernel_meminfo, swap_total)},
        {SYSAPI_SWAP_FREE, offsetof(struct sysapi_kernel_meminfo, swap_free)},
        {SYSAPI_DIRTY, offsetof(struct sysapi_kernel_meminfo, dirty)},
        {SYSAPI_WRITEBACK, offsetof(struct sysapi_kernel_meminfo, writeback)},
        {SYSAPI_ANONPAGES, offsetof(struct sysapi_kernel_meminfo, anonpages)},
        {SYSAPI_BOUNCE, offsetof(struct sysapi_kernel_meminfo, bounce)},
        {SYSAPI_WRITEBACK_TMP, offsetof(struct sysapi_kernel_meminfo, writebacktmp)},
        {SYSAPI_COMMIT_LIMIT, offsetof(struct sysapi_kernel_meminfo, commitlimit)},
        {SYSAPI_MAPPED, offsetof(struct sysapi_kernel_meminfo, mapped)},
        {SYSAPI_SHMEM, offsetof(struct sysapi_kernel_meminfo, shmem)},
        {SYSAPI_SLAB, offsetof(struct sysapi_kernel_meminfo, slab)},
        {SYSAPI_SRECLAIMABLE, offsetof(struct sysapi_kernel_meminfo, sreclaimable)},
        {SYSAPI_SUNRECLAIM, offsetof(struct sysapi_kernel_meminfo, sunreclaim)},
        {SYSAPI_KERNEL_STACK, offsetof(struct sysapi_kernel_meminfo, kernelstack)},
        {SYSAPI_PAGE_TABLE, offsetof(struct sysapi_kernel_meminfo, pagetables)},
        {SYSAPI_NFS_UNSTABLE, offsetof(struct sysapi_kernel_meminfo, nfs_unstable)},
        {SYSAPI_COMMITED_AS, offsetof(struct sysapi_kernel_meminfo, commited_as)},
        {SYSAPI_VMALLOC_TOTAL, offsetof(struct sysapi_kernel_meminfo, vmalloctotal)},
        {SYSAPI_VMALLOC_USED, offsetof(struct sysapi_kernel_meminfo, vmallocchunk)},
        {SYSAPI_VMALLOC_CHUNK, offsetof(struct sysapi_kernel_meminfo, vmallocchunk)},
        {SYSAPI_HARDWARE_CORRUPTED, offsetof(struct sysapi_kernel_meminfo, hardwarecorrupted)},
        {SYSAPI_ANONPAGES, offsetof(struct sysapi_kernel_meminfo, anonpages)},
        {SYSAPI_CMA_TOTAL, offsetof(struct sysapi_kernel_meminfo, cmatotal)},
        {SYSAPI_CMA_FREE, offsetof(struct sysapi_kernel_meminfo, cmafree)},
        {SYSAPI_HUGE_PAGES_TOTAL, offsetof(struct sysapi_kernel_meminfo, hugepagestotal)},
        {SYSAPI_HUGE_PAGES_FREE, offsetof(struct sysapi_kernel_meminfo, hugepagesfree)},
        {SYSAPI_HUGE_PAGES_RSVD, offsetof(struct sysapi_kernel_meminfo, hugepagesrsvd)},
        {SYSAPI_HUGE_PAGES_SURP, offsetof(struct sysapi_kernel_meminfo, hugepagessurp)},
        {SYSAPI_HUGE_PAGE_SIZE, offsetof(struct sysapi_kernel_meminfo, hugepagesize)},
        {SYSAPI_DIRECT_MAP4K, offsetof(struct sysapi_kernel_meminfo, directmap4k)},
        {SYSAPI_DIRECT_MAP2M, offsetof(struct sysapi_kernel_meminfo, directmap2m)}

    };

    int size = sizeof(_meminfo) / sizeof(_meminfo[0]);
    int i;
    FILE *fp;

    fp = fopen(PROC_MEM_INFO, "r");
    if (!fp)
        return -1;

    char buff[2000];

    memset(buff, 0, sizeof(buff));

    while (fgets(buff, sizeof(buff), fp)) {
        int j;
        int list;


        char src[20], dst[20];

        i = 0;

        while (buff[i] != ':') {
            src[i] = buff[i];
            i++;
        }

        src[i] = '\0';

        i++;

        while (buff[i] == ' ')
            i++;

        if (buff[i] == '\n' || buff[i] == '\0')
            continue;

        j = 0;

        while (buff[i]) {
            if ((buff[i] == '\n') || (buff[i] == '\0'))
                break;

            if (buff[i] != ' ')
                dst[j] = buff[i];
            else
                break;

            i++;

            j++;
        }

        dst[j] = '\0';

        for (list = 0; list < size; list++) {
            if (strcmp(_meminfo[list].name, src) == 0) {
                int *value = (long)((long)(meminfo) + _meminfo[list].off);

                *value = atoi(dst);
            }
        }
    }

    fclose(fp);

    return 0;
}

#ifdef CONFIG_SYSAPI_PROC_TEST
int main(void)
{
    char cmdline[200];
    struct sysapi_kernel_meminfo meminfo;

    int ret;

    ret = sysapi_get_kernel_cmdline(cmdline);
    ret = sysapi_get_kernel_meminfo(&meminfo);

    return ret;
}
#endif

