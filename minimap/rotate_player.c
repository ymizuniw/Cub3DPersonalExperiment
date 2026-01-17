#include "includes/player.h"
#include <math.h>

void wrap_radian(float *angle_radian)
{
    *angle_radian = fmod(*angle_radian, 2.0f * M_PI);
    if (*angle_radian<0)
        *angle_radian += 2.0f * M_PI;
}

void rotate_vec(float *x, float *y, float angle_radian)
{
    float old_x;
    float old_y;
    old_x = *x;
    old_y = *y;

    wrap_radian(&angle_radian);
    *x = old_x * cosf(angle_radian) - old_y*sinf(angle_radian);
    *y = old_x * sinf(angle_radian) + old_y*cosf(angle_radian);
}

void rotate_player(t_player *player, float angle_radian)
{
    rotate_vec(&player->dir_x, &player->dir_y, angle_radian);
    /*
        rotate plane
    */
    {
        float len;
        len = sqrtf(player->dir_x * player->dir_x + player->dir_y *player->dir_y);
        if (len>0.0f)
        {
            player->dir_x /= len;
            player->dir_y /= len;
        }
    }
}
