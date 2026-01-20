#include "../../include/core/game.h"
#include "../../minilibx_opengl_20191021/mlx.h"

int	game_mlx_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	return (1);
}

int	game_mlx_new_window(t_game *game, int win_w, int win_h)
{
	game->win = mlx_new_window(game->mlx, win_w, win_h, "test_init_game");
	if (!game->win)
		return (-1);
	return (1);
}

int	game_mlx_new_image(t_game *game, int win_w, int win_h)
{
	game->frame.w = win_w;
	game->frame.h = win_h;
	game->frame.img = mlx_new_image(game->mlx, win_w, win_h);
	if (!game->frame.img)
		return (-1);
	game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (-1);
	return (1);
}
