#include "includes/game.h"
#include "includes/player.h"

void draw_player_dir(t_game *game)
{
    float line_len = 1.0f;
    int color = 0x00FFAA00;

    //set (x,y) of start/end cell
    float start_cell_x = game->player.x;
    float start_cell_y = game->player.y;
    float end_cell_x = start_cell_x + game->player.dir_x * line_len;
    float end_cell_y = start_cell_y + game->player.dir_y * line_len;

    //mapping to pixel
    int start_pixel_x = game->mm.ox + (int)(start_cell_x * game->mm.tile_size);
    int start_pixel_y = game->mm.oy + (int)(start_cell_y * game->mm.tile_size);
    int end_pixel_x = game->mm.ox + (int)(end_cell_x * game->mm.tile_size);
    int end_pixel_y = game->mm.oy + (int)(end_cell_y * game->mm.tile_size);

    draw_line(&game->frame, start_pixel_x, start_pixel_y, end_pixel_x, end_pixel_y, color);
}
