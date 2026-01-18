#include "includes/player.h"
#include <unistd.h>
#include <stdio.h>

void player_set_dir(t_player *player, char c)
{
    if (c == 'N')
    {
        player->dir.x = 0.0f;
        player->dir.y = -1.0f;
    }
    else if (c=='S')
    {
        player->dir.x = 0.0f;
        player->dir.y = 1.0f;
    }
    else if (c=='E')
    {
        player->dir.x = 1.0f;
        player->dir.y = 0.0f;
    }
    else if (c=='W')
    {
        player->dir.x = -1.0f;
        player->dir.y = 0.0f;
    }
}
