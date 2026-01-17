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
int on_close(void *param);

//minimap
void fill_rect(t_img *img, int x0, int y0, int w, int h, int color);
int is_wall(const t_map_info *map_info, int x, int y);
void minimap_render(t_game *game);

//player move in minimap
int on_wsad(int keycode, t_game *game);

#endif
