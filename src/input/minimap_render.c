#include "../../include/core/game.h"
#include "../../include/core/graphics.h"
#include "../../include/input/minimap_render.h"

void	minimap_render(t_game *game)
{
	int		wall;
	int		player;
	int		x;
	int		y;
	float	px;
	float	py;
	int		sx;
	int		sy;
	int		dot;

	wall = 0xFFFFFF;
	player = 0xFF0000;
	y = 0;
	while (y < game->map_info.map_rows)
	{
		x = 0;
		while (x < game->map_info.map_cols)
		{
			if (is_wall(&game->map_info, x, y))
				fill_rect(&game->frame, game->mm.ox + x * game->mm.tile_size,
					game->mm.oy + y * game->mm.tile_size, game->mm.tile_size,
					game->mm.tile_size, wall);
			x++;
		}
		y++;
	}
	{
		px = game->player.pos.x;
		py = game->player.pos.y;
		sx = game->mm.ox + (int)(px * game->mm.tile_size);
		sy = game->mm.oy + (int)(py * game->mm.tile_size);
		dot = 5;
		fill_rect(&game->frame, sx - dot / 2, sy - dot / 2, dot, dot, player);
	}
	draw_player_dir(game);
}
