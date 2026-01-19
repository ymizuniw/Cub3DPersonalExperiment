#include "../../common/includes/game.h"
#include "../../common/includes/graphics.h"
#include "../../common/includes/input.h"
#include "../includes/minimap_render.h"
#include "../../minilibx_opengl_20191021/mlx.h"
#include "../../parse_map/includes/map_info.h"
#include "../../parse_map/includes/parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int			fd;
	t_map_info	map_info;
	t_game		game;
	int			game_init_ret;

	fd = open("../../parse_map/test/data/valid_simple.cub", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	map_info_init(&map_info);
	if (parse_data(fd, &map_info) < 0)
	{
		printf("parse_data failed\n");
		close(fd);
		map_info_destroy(&map_info);
		return (1);
	}
	close(fd);
	memset(&game, 0, sizeof(game));
	game_init_ret = game_init(&game, &map_info, 900, 900);
	if (game_init_ret < 0)
	{
		printf("game_init failed\n");
		game_destroy(&game);
		return (1);
	}
	minimap_render(&game);
	mlx_hook(game.win, 17, 0, on_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
