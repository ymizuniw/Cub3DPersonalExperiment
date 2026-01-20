#include "../../include/core/game.h"
#include "../../include/core/graphics.h"
#include "../../include/core/input.h"
#include "../../include/input/minimap_render.h"
#include "../../include/map_parser/map_info.h"
#include "../../include/map_parser/parser.h"
#include "../../minilibx_opengl_20191021/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int		raycasting(t_game *game);

#define WIN_W 900
#define WIN_H 900

int	game_loop(t_game *game)
{
	clear_img(&game->frame, 0x000000);
	raycasting(game);
	minimap_render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, on_close, game);
	mlx_hook(game->win, 2, 1L << 0, on_keypress, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	map_info;
	int			parse_data_ret;
	t_game		game;
	int			game_init_ret;

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open map file %s\n", argv[1]);
		return (1);
	}
	map_info_init(&map_info);
	parse_data_ret = parse_data(fd, &map_info);
	close(fd);
	if (parse_data_ret < 0)
	{
		printf("Error: Invalid map file format\n");
		map_info_destroy(&map_info);
		return (1);
	}
	game_init_ret = game_init(&game, &map_info, WIN_W, WIN_H);
	if (game_init_ret < 0)
	{
		printf("Error: Failed to initialize game\n");
		game_destroy(&game);
		return (1);
	}
	setup_hooks(&game);
	printf("Cub3D started successfully!\n");
	printf("Controls:\n");
	printf("  WASD - Move\n");
	printf("  Left/Right arrows - Rotate\n");
	printf("  ESC or close window - Exit\n");
	mlx_loop(game.mlx);
	return (0);
}
