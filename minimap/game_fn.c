#include "includes/game.h"
#include "../minilibx_opengl_20191021/mlx.h"
#include "string.h"
#include <stdlib.h>

int game_mlx_init(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (-1);
    return (1);
}

int game_mlx_new_window(t_game *game, int win_w, int win_h)
{
    game->win = mlx_new_window(game->mlx, win_w, win_h, "test_init_game");
    if (!game->win)
        return (-1);
    return (1);
}

int game_mlx_new_image(t_game *game, int win_w, int win_h)
{
    game->frame.w = win_w;
    game->frame.h = win_h;
    game->frame.img = mlx_new_image(game->mlx, win_w, win_h);
    if (!game->frame.img)
        return (-1);
    game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp, &game->frame.line_len, &game->frame.endian);
    if (!game->frame.addr)
        return (-1);
    return (1);
}

int game_init(t_game *game, t_map_info *map_info, int win_w, int win_h)
{
    memset(game, 0, sizeof(*game));
    game->map = *map_info;
    memset(map_info, 0, sizeof(t_map_info));
    if (game_mlx_init(game) < 0) return (-1);
    if (game_mlx_new_window(game, win_w, win_h) < 0) return (-1);
    if (game_mlx_new_image(game, win_w, win_h) < 0) return (-1);
    return (1);
}

int game_destroy(t_game *game)
{
    mlx_destroy_image(game->mlx, game->frame.img);
    mlx_destroy_window(game->mlx, game->win);
    map_info_destroy(&game->map);
    return (1);
}

int on_close(void *param)
{
    t_game *game = (t_game *)param;
    game_destroy(game);
    exit(0);
    return (0);
}
