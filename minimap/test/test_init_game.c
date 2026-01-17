#include "../includes/game.h"
#include "../../parse_map/includes/parser.h"
#include "../../minilibx_opengl_20191021/mlx.h"
#include "../../parse_map/includes/map_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define WIN_W 900
#define WIN_H 900

// typedef struct s_game
// {
//     void *mlx;
//     void *win;
//     t_img frame;
//     t_map_info map;
//     t_player player;
//     t_minimap mm;
// }t_game;

int main(void)
{
    int fd = open("../../parse_map/test/data/valid_simple.cub", O_RDONLY);
    if (fd<0)
        return (1);
    t_map_info map_info;
    map_info_init(&map_info);
    int parse_data_ret = parse_data(fd, &map_info);
    if (parse_data_ret<0)
        return(1);
    close(fd);

    t_game game;
    //the ownership of map is delegated to t_game
    int game_init_ret = game_init( &game, &map_info,900, 900);
    if (game_init_ret<0)
    {
        //if window or mlx is NULL, it refers to undefined memory?
        game_destroy(&game);
        return(1);
    }
    mlx_hook(game.win, 17, 0, on_close, &game);
    mlx_loop(game.mlx);
    return (0);
}
