#ifndef RAY_H
#define RAY_H

#include "../../vector/includes/vec2.h"

//from(x,y), to (dir_x, dir_y)
/*
    start position:
    float x,y;
    unit: cell-space;
    init with player.x, player.y;
*/

/*
    float dir_x, dir_y;
    west : (-1,0)
    east: (1,0)
    north: (0,1)
    south: (0,-1)
*/

/*
    int map_x, map_y;
    the cell ray belongs;
    init with:
        map_x = (int)x;
        map_y = (int)y;
    this coordination will be used to judge wall collision.
*/

/*
    floa delta_x, delta_y;
    delta_x = fabs(1.0f / dir_x);
    delta_y = fabs(1.0f / dir_y);

*/

/*
    float side_x, side_y;
    the distance between the current position to the next x/y grid;
    init with appropriate value, and accumulates with discrete number;
    if (dir_x < 0)
        side_x = (x-map_x) * delta_x;
    else
        side_x = (map_x + 1.0f - x) * delta_x;

    if (side_x < side_y)
    {
        side_x += delta_x;
        map_x += step_x;
        hit_side = X_SIDE;
    }
    else
    {
        side_y += delta_y;
        map_y += step_y;
        hit_side = Y_SI
    }
*/

typedef struct s_ray
{
    //start position
    t_vec2 pos;
    t_vec2 dir;

    //dda state
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    float   side_x;
    float   side_y;
    float   delta_x;
    float   delta_y;
} t_ray;

typedef struct s_ray_hit
{
    int     hit;
    char    side;
    int     cell_x;
    int     cell_y;
    float   perpendicular_dist;
    float   hit_x;
    float   hit_y;
} t_ray_hit;

#endif
