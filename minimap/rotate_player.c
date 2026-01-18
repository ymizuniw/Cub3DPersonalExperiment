#include "includes/player.h"
#include "../vector/includes/vec2.h"
#include <stdio.h>

void rotate_player(t_player *player, float angle_radian)
{
    player->dir = rotate_v2(player->dir, angle_radian);
    printf("dir: %f,%f\nangle_radian: %f\n", player->dir.x, player->dir.y, angle_radian);
    /*
        rotate plane
    */
}
