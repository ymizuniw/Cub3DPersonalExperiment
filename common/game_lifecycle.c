#include "../minilibx_opengl_20191021/mlx.h"
#include "includes/game.h"
#include "string.h"
#include <stdlib.h>

int	game_init(t_game *game, t_map_info *map_info, int win_w, int win_h)
{
	memset(game, 0, sizeof(*game));
	game->map_info = *map_info;
	game_player_init(game);
	game_minimap_init(game);
	map_info->map = NULL;
	map_info->north_texture = NULL;
	map_info->south_texture = NULL;
	map_info->west_texture = NULL;
	map_info->east_texture = NULL;
	if (game_mlx_init(game) < 0)
		return (-1);
	if (game_mlx_new_window(game, win_w, win_h) < 0)
		return (-1);
	if (game_mlx_new_image(game, win_w, win_h) < 0)
		return (-1);
	return (1);
}

int	game_destroy(t_game *game)
{
	mlx_destroy_image(game->mlx, game->frame.img);
	mlx_destroy_window(game->mlx, game->win);
	map_info_destroy(&game->map_info);
	return (1);
}
