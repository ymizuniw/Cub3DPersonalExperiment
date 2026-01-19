#include "../vector/includes/vec2.h"
#include "includes/player.h"
#include <stdio.h>

void	rotate_player(t_player *player, float angle_radian)
{
	player->dir = rotate_v2(player->dir, angle_radian);
}
