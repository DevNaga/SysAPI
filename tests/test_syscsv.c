#include "../core/sysapi.h"

int row = 0;

void csv_file(struct csv_coldata *coldata, int coldata_len)
{
    char *data;
    int i;

    for (i = 0; i < coldata_len; i++) {
        data = coldata[i].data;
        printf("row: %d col : %d data : %s\n", row, coldata[i].col, data);
    }

    row++;
}

int main(void) {
    char *csvfile = "csvfile.csv";
    int ret;

    ret = sysapi_get_csvline(csvfile, csv_file);
    if (ret < 0)
        return -1;

    return 0;
}

