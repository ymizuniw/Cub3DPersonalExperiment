#include "includes/game.h"
#include "../minilibx_opengl_20191021/mlx.h"

void minimap_render(t_game *game)
{
    int bg = 0x000000;
    int wall = 0xFFFFFF;
    int player = 0xFF0000;
    int x;
    int y;

    clear_img(&game->frame, bg);
    y = 0;
    while(y<game->map.map_rows)
    {
        x = 0;
        while(x<game->map.map_cols)
        {
            if (is_wall(&game->map, x, y))
                fill_rect(&game->frame, game->mm.ox + x * game->mm.tile_size, game->mm.oy + y *game->mm.tile_size, game->mm.tile_size, game->mm.tile_size, wall);
            x++;
        }
        y++;
    }
    {
        float px = game->player.pos.x;
        float py = game->player.pos.y;
        int sx = game->mm.ox + (int)(px * game->mm.tile_size);
        int sy = game->mm.oy + (int)(py * game->mm.tile_size);
        int dot = 5;
        fill_rect(&game->frame, sx - dot/2, sy - dot/2, dot, dot, player);
    }
    draw_player_dir(game);
    mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0,0);
}
