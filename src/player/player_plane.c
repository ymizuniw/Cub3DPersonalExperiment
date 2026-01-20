#include "../../include/core/player.h"
#include <math.h>

void	player_init_plane_from_dir(t_player *player)
{
	player->plane.x = -player->dir.y * 0.66f;
	player->plane.y = player->dir.x * 0.66f;
}

void	player_rotate_plane(t_player *player, float angle_radian)
{
	float	cos_angle;
	float	sin_angle;

	float old_dir_x, old_plane_x;
	cos_angle = cosf(angle_radian);
	sin_angle = sinf(angle_radian);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos_angle - player->dir.y * sin_angle;
	player->dir.y = old_dir_x * sin_angle + player->dir.y * cos_angle;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos_angle - player->plane.y * sin_angle;
	player->plane.y = old_plane_x * sin_angle + player->plane.y * cos_angle;
}
