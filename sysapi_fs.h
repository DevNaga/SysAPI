#ifndef __SYSAPI_FS_H__
#define __SYSAPI_FS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

typedef enum {
	SYSAPI_FILE_TYPE_REGFILE,
	SYSAPI_FILE_TYPE_DIRECT,
} sysapi_file_type;

int sysapi_read_dir(char *dirpath,
	                void (*callback)(char *filename, sysapi_file_type type, void *app_cb),
					void *app_cb);
int sysapi_read_binfile(char *filename,
		                void (*callback)(char *filedata, int len, void *app_ctx),
						void *app_ctx);

#endif

