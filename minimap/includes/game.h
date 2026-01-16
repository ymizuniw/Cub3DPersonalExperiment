#ifndef GAME_H
#define GAME_H

#include "minimap.h"
#include "image.h"
#include "player.h"
#include "../../parse_map/includes/map_info.h"

typedef struct s_game
{
    void *mlx;
    void *win;
    t_img frame;
    t_map_info map;
    t_player player;
    t_minimap mm;
}t_game;

int game_mlx_init(t_game *game);
int game_mlx_new_window(t_game *game, int win_w, int win_h);
int game_mlx_new_image(t_game *game, int win_w, int win_h);
int game_init(t_game *game, t_map_info *map_info, int win_w, int win_h);
int game_destroy(t_game *game);

#endif
