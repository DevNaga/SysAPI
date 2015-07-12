#include "sysapi_csv.h"
#include "sysapi_csv_i.h"

int sysapi_get_csvcols(char *csvline)
{
    int count = 1;
    char *line = csvline;

    while (*line != '\0') {
        if (*line == ',')
            count++;
        line++;
    }

    return count;
}

static void __sysapi_skip_csv_header(FILE *fp)
{
    while (fgetc(fp) != '\n');
}

static void __sysapi_strcut(char *string, void (*cbf)(struct csv_coldata *coldata, int coldata_len))
{
#define MAX_COLS 255
    int len;
    int i;
    char *loc;
    int pos = 0;
    int col = 0;
    struct csv_coldata coldata[MAX_COLS];
    int length = strlen(string) - 1;

    while (pos <= length) {
        loc = strchr(string + pos, ',');
        if (loc) {
            len = loc - &string[pos];
            if (len > 0) {
                if (col >= MAX_COLS)
                    break;

                coldata[col].data = strndup(string + pos, len);
                coldata[col].col = col + 1;
                col++;
            } else {
                return;
            }
            pos += len + 1;
        } else {
            coldata[col].data = strdup(string + pos);
            coldata[col].col = col + 1;
            col++;
            break;
        }
    }

    cbf(coldata, col);

    for (i = 0; i < col; i++)
        free(coldata[i].data);
}

int sysapi_get_csvline(char *filename,
                       void (*cbf)(struct csv_coldata *coldata, int coldata_len))
{
    FILE *fp;
    char buf[1024];

    fp = fopen(filename, "r");
    if (!fp)
        return -1;

    __sysapi_skip_csv_header(fp);

    while (fgets(buf, sizeof(buf), fp)) {
        __sysapi_strcut(buf, cbf);
    }
    
    fclose(fp);

    return 0;
}

