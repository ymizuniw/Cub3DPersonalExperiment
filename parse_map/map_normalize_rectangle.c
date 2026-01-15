// #include "includes/map_info.h"
#include <string.h>
#include <stdlib.h>

//this won't own map[].
char *map_normalize_rectangle(char *map[], int row_max, int col_max)
{
    size_t i = 0;
    size_t len;

    char *new_map = (char *)malloc(row_max * col_max);
    if (new_map==NULL)
        return (NULL);
    while(i<(size_t)row_max)
    {
        char elem;
        size_t j;
        len = strlen(map[i]);
        j = 0;
        while(j<(size_t)col_max)
        {
            if (j<len)
                elem = map[i][j];
            else
                elem = ' ';
            new_map[i*col_max + j] = elem;
            j++;
        }
        i++;
    }
    return (new_map);
}
