// #include "includes/map_builder.h"
#include "includes/map_info.h"
#include <stdlib.h>
#include <stdio.h>

int is_direction(char c)
{
    if (c=='N' || c=='S' || c=='E' || c=='W')
        return (1);
    return (0);
}

int map_scan_set_start(char *map, int row_max, int col_max, int start[2], char *direction)
{
    int i = 0;
    int j = 0;

    bool start_flag = false;
    while (!(i==row_max && j==col_max))
    {
        j = 0;
        while (j<col_max)
        {
            if (is_direction(map[i*col_max + j]))
            {
                if (start_flag==false)
                {
                    start[0] = i;
                    start[1] = j;
                    *direction = map[i*col_max + j];
                    start_flag = true;
                }
                else {
                    fprintf(stderr, "map_scan_set_start: multiple start point err\n");
                    start[0]=-1;
                    start[1]=-1;
                    *direction = '?';
                    return (-1);
                }
            }
            j++;
        }
        i++;
    }
    if (start_flag)
        return (1);
    fprintf(stderr, "map_scan_set_start: no start point found\n");
    return (-1);
}
