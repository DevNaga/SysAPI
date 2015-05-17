#include <stdio.h>

void sapi_insert_sort(int *ar, int size)
{
    int i, j;
    int t;

    for (i = 1; i < size - 1; i++) {
        t = ar[i];
        for (j = i - 1; (j >= 0) && (ar[j] > t); j--) {
            ar[j + 1] = ar[j];
        }
        ar[j + 1] = t;
    }

    printf("\n");
}

#ifdef CONFIG_SAPI_INSORT_TEST
int main()
{
    int i;
    int ar[] = {10, 20, 11, 5, 1, 2, 6, 9, 122};
    int size = sizeof(ar) / sizeof(ar[0]);

    printf("array size %d\n", size);

    sapi_insert_sort(ar, size);


    for (i = 0; i < size; i++) {
        printf("elem: %d\n", ar[i]);
    }

    return 0;
}

#endif

