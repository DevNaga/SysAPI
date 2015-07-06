#ifndef __SYSAPI_CSV_I_H__
#define __SYSAPI_CSV_I_H__

static void __sysapi_skip_csv_header(FILE *fp);

static void __sysapi_strcut(char *string,
                            void (*cbf)(struct csv_coldata *coldata,
                                        int coldata_len));

#endif

