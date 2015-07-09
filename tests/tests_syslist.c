#include "../sysapi_list.h"

void *list;
struct sapi_list *list_item;

int free_list(void *ptr, void *data)
{
    free(data);
    return 0;
}

int main(void)
{
    int list_size = 200;
    list = sapi_list_init();
    if (!list)
        return -1;
    
    int i;
    
    for (i = 0; i < list_size; i++) {
        int *new_elem;
        
        new_elem = calloc(1, sizeof(new_elem));
        if (!new_elem)
            return -1;
        
        *new_elem = i;
        
        sapi_list_add_tail(list, new_elem);
    }
    
    sapi_list_foreach(list, list_item) {
        int *ele = sapi_list_item_data(list_item);
        if (ele)
            printf("%d\n", *ele);
    }
    
    sapi_list_deinit(list, NULL, free_list);

    return 0;
}
