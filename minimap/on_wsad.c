#include "../common/includes/game.h"
#include "../common/includes/player.h"
#include "includes/minimap_render.h"
#include "includes/player_move.h"

int	on_wsad(int keycode, t_game *game)
{
	float	step;
	float	new_x;
	float	new_y;

	step = 0.10f;
	// Move forward/backward along direction vector
	if (keycode == 13) // W - forward
	{
		new_x = game->player.pos.x + game->player.dir.x * step;
		new_y = game->player.pos.y + game->player.dir.y * step;
	}
	else if (keycode == 1) // S - backward
	{
		new_x = game->player.pos.x - game->player.dir.x * step;
		new_y = game->player.pos.y - game->player.dir.y * step;
	}
	// Strafe left/right perpendicular to direction
	else if (keycode == 0) // A - left
	{
		new_x = game->player.pos.x + game->player.dir.y * step;
		new_y = game->player.pos.y - game->player.dir.x * step;
	}
	else if (keycode == 2) // D - right
	{
		new_x = game->player.pos.x - game->player.dir.y * step;
		new_y = game->player.pos.y + game->player.dir.x * step;
	}
	else
		return (0);
	// Check collision and update position
	if (!is_wall(&game->map_info, (int)new_x, (int)new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
	return (0);
}
