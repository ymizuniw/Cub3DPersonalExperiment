#include "../../include/core/player.h"
#include <stdio.h>
#include <unistd.h>

void	player_set_dir(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir.x = 0.0f;
		player->dir.y = -1.0f;
	}
	else if (c == 'S')
	{
		player->dir.x = 0.0f;
		player->dir.y = 1.0f;
	}
	else if (c == 'E')
	{
		player->dir.x = 1.0f;
		player->dir.y = 0.0f;
	}
	else if (c == 'W')
	{
		player->dir.x = -1.0f;
		player->dir.y = 0.0f;
	}
	
	player_init_plane_from_dir(player);
}
