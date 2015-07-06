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
#include <sys/shm.h>
#include <sys/mman.h>

typedef enum {
	SYSAPI_FILE_TYPE_REGFILE,
	SYSAPI_FILE_TYPE_DIRECT,
} sysapi_file_type;

int sysapi_dir_read(char *dirpath,
	                void (*callback)(char *filename, sysapi_file_type type, void *app_cb),
					void *app_cb);
int sysapi_read_binfile(char *filename,
		                void (*callback)(char *filedata, int len, void *app_ctx),
						void *app_ctx);

void *sysapi_get_maped_fdata_ptr(void *sfmap);

void sysapi_async_unmap_file(void *sfmap);

void sysapi_sync_unmap_file(void *sfmap);

void sysapi_unmap_file(void *sfmap);

void *sysapi_map_file_rd(char *filename);

void *sysapi_map_file_rdwr(char *filename);

int sysapi_get_symlink_count(char *filename);

int sysapi_get_filesize(char *filename);

int sysapi_file_exist(char *filename);

int sysapi_dir_walk(char *dirpath,
                    void (*callback)(char *parent, sysapi_file_type file_type, char *filename, void *app_ctx),
                    void *app_ctx);

int sysapi_makedir(char *dirname);

int sysapi_touch(char *filename);

int sysapi_create_pidfile(char *filename);

int sysapi_describe_link(char *linkpath, char *actualname, int actual_len);

int sysapi_create_symlink(char *original_file_path, char *symlink_path);

int sysapi_list_dir(char *dirpath,
                    void (*callback)(char *dirname, void *ctx),
                    void *ctx);

#endif
