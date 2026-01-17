#include "includes/player.h"
#include <unistd.h>
#include <stdio.h>

void player_set_dir(t_player *player, char c)
{
    if (c == 'N')
    {
        player->dir_x = 0.0f;
        player->dir_y = -1.0f;
    }
    else if (c=='S')
    {
        player->dir_x = 0.0f;
        player->dir_y = 1.0f;
    }
    else if (c=='E')
    {
        player->dir_x = 1.0f;
        player->dir_y = 0.0f;
    }
    else if (c=='W')
    {
        player->dir_x = -1.0f;
        player->dir_y = 0.0f;
    }
}
