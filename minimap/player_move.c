#include "includes/game.h"
#include "includes/player.h"
#include <unistd.h>
#include <stdio.h>

// int on_wsad(int keycode, t_game *game)
// {
//     float step = 0.10f;
//     printf("keycode:%d\n", keycode);
//     if (keycode == 13)
//         game->player.y -= step;
//     if (keycode == 1)
//         game->player.y += step;
//     if (keycode == 0)
//         game->player.x -= step;
//     if (keycode == 2)
//         game->player.x += step;
//     minimap_render(game);
//     return (0);
// }

int on_wsad(int keycode, t_game *game)
{
    float step = 0.10f;
    float dx = 0.0f;
    float dy = 0.0f;

    printf("keycode:%d\n", keycode);
    if (keycode == 13)
        dy = -1.0f;
    if (keycode == 1)
        dy = 1.0f;
    if (keycode == 0)
        dx = -1.0f;
    if (keycode == 2)
        dx = 1.0f;
    if (dx!=0.0f || dy != 0.0f)
    {
        float new_x = game->player.x + dx * step;
        float new_y = game->player.y + dy * step;
        if (!is_wall(&game->map, new_x, new_y))
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
        minimap_render(game);
    }
    return (0);
}
