
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
