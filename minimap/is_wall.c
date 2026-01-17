#include "includes/image.h"
#include "includes/game.h"

int is_wall(const t_map_info *map_info, int x, int y)
{
    //beyond wall
    if (x<0 || y <0 || x>= map_info->map_cols || y >= map_info->map_rows)
        return (1);
    //is wall
    if (map_info->map[y*map_info->map_cols + x]=='1')
        return (1);
    //not wall
    return (0);
}
