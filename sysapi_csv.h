#ifndef __SYSAPI_CSV_H__
#define __SYSAPI_CSV_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct csv_coldata {
    int col;
    char *data;
};

int sysapi_get_csvcols(char *csvline);

int sysapi_get_csvline(char *filename,
                       void (*cbf)(struct csv_coldata *coldata,
						           int coldata_len));

#endif

