#include "../../include/core/game.h"
#include "../../include/core/player.h"
#include "minimap_render.h"
#include "player_move.h"

int	on_wsad(int keycode, t_game *game)
{
	float	step;
	float	new_x;
	float	new_y;

	step = 0.10f;
	
	if (keycode == 13) 
	{
		new_x = game->player.pos.x + game->player.dir.x * step;
		new_y = game->player.pos.y + game->player.dir.y * step;
	}
	else if (keycode == 1) 
	{
		new_x = game->player.pos.x - game->player.dir.x * step;
		new_y = game->player.pos.y - game->player.dir.y * step;
	}
	
	else if (keycode == 0) 
	{
		new_x = game->player.pos.x + game->player.dir.y * step;
		new_y = game->player.pos.y - game->player.dir.x * step;
	}
	else if (keycode == 2) 
	{
		new_x = game->player.pos.x - game->player.dir.y * step;
		new_y = game->player.pos.y + game->player.dir.x * step;
	}
	else
		return (0);
	
	if (!is_wall(&game->map_info, (int)new_x, (int)new_y))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}
	return (0);
}
