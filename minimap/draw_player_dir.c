#include "../common/includes/game.h"
#include "../common/includes/graphics.h"
#include "../common/includes/player.h"

void	draw_player_dir(t_game *game)
{
	float	line_len;
	int		color;
	float	start_cell_x;
	float	start_cell_y;
	float	end_cell_x;
	float	end_cell_y;
	int		start_pixel_x;
	int		start_pixel_y;
	int		end_pixel_x;
	int		end_pixel_y;

	line_len = 1.0f;
	color = 0x00FFAA00;
	// set (x,y) of start/end cell
	start_cell_x = game->player.pos.x;
	start_cell_y = game->player.pos.y;
	end_cell_x = start_cell_x + game->player.dir.x * line_len;
	end_cell_y = start_cell_y + game->player.dir.y * line_len;
	// mapping to pixel
	start_pixel_x = game->mm.ox + (int)(start_cell_x * game->mm.tile_size);
	start_pixel_y = game->mm.oy + (int)(start_cell_y * game->mm.tile_size);
	end_pixel_x = game->mm.ox + (int)(end_cell_x * game->mm.tile_size);
	end_pixel_y = game->mm.oy + (int)(end_cell_y * game->mm.tile_size);
	draw_line(&game->frame, start_pixel_x, start_pixel_y, end_pixel_x,
		end_pixel_y, color);
}
