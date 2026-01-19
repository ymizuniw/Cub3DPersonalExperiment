#include "../../common/includes/game.h"
#include "../../common/includes/graphics.h"
#include "../../common/includes/input.h"
#include "../../minilibx_opengl_20191021/mlx.h"
#include "../../parse_map/includes/map_info.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void	draw_line_tests(t_game *g)
{
	clear_img(&g->frame, 0x000000);
	/* 十字 */
	draw_line(&g->frame, 50, 50, 300, 50, 0xFFFFFF);    // →
	draw_line(&g->frame, 300, 70, 50, 70, 0xFFFFFF);    // ←
	draw_line(&g->frame, 80, 100, 80, 300, 0xFFFFFF);   // ↓
	draw_line(&g->frame, 100, 300, 100, 100, 0xFFFFFF); // ↑
	/* 斜め */
	draw_line(&g->frame, 200, 200, 350, 350, 0xFF0000); // 右下
	draw_line(&g->frame, 200, 200, 350, 50, 0x00FF00);  // 右上
	draw_line(&g->frame, 200, 200, 50, 350, 0x0000FF);  // 左下
	draw_line(&g->frame, 200, 200, 50, 50, 0xFFFF00);   // 左上
	/* 急/緩 */
	draw_line(&g->frame, 450, 50, 480, 300, 0xFFFFFF); // 急
	draw_line(&g->frame, 500, 50, 800, 100, 0xFFFFFF); // 緩
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

int	main(void)
{
	int			fd;
	t_map_info	map_info;
	t_game		game;
	int			game_init_ret;

	// fd = open("../../parse_map/test/data/valid_jagged_map.cub", O_RDONLY);
	// if (fd<0)
	// {
	//     perror("open");
	//     return(1);
	// }
	// map_info_init(&map_info);
	// if (parse_data(fd, &map_info)<0)
	// {
	//     printf("parse_data failed\n");
	//     close(fd);
	//     map_info_destroy(&map_info);
	//     return (1);
	// }
	// close(fd);
	memset(&game, 0, sizeof(game));
	game_init_ret = game_init(&game, &map_info, 900, 900);
	if (game_init_ret < 0)
	{
		printf("game_init failed\n");
		game_destroy(&game);
		return (1);
	}
	draw_line_tests(&game);
	// mlx_put_image_to_window(game.mlx, game.win, game.frame.img, 0,0);
	// minimap_render(&game);
	mlx_hook(game.win, 17, 0, on_close, &game);
	// mlx_hook(game.win, 2, 0, on_wsad, &game);
	mlx_loop(game.mlx);
	return (0);
}
