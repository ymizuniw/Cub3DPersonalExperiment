#include "includes/game.h"
#include "../minilibx_opengl_20191021/mlx.h"

void minimap_render(t_game *game)
{
    //game->mm:
    int tile = 16;
    int ox = 20;
    int oy = 20;

    int bg = 0x000000;
    int wall = 0xFFFFFF;
    //game->player:
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
                fill_rect(&game->frame, ox + x * tile, oy + y *tile, tile, tile, wall);
            x++;
        }
        y++;
    }
    {
        float px = (float)game->map.start_x + 0.5f;
        float py = (float)game->map.start_y + 0.5f;
        int sx = ox + (int)(px * tile);
        int sy = oy + (int)(py * tile);
        int dot = 5;
        fill_rect(&game->frame, sx - dot/2, sy - dot/2, dot, dot, player);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0,0);
}
