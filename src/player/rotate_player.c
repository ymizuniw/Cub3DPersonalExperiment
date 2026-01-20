#include "../../include/core/player.h"
#include "../../vector/includes/vec2.h"

void	rotate_player(t_player *player, float angle_radian)
{
	player->dir = rotate_v2(player->dir, angle_radian);
	player->plane = rotate_v2(player->plane, angle_radian);
}
