#include "includes/game.h"
#include "includes/player.h"
#include <unistd.h>
#include <stdio.h>

int on_wsad(int keycode, t_game *game)
{
    float step = 0.10f;
    float dx = 0.0f;
    float dy = 0.0f;

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
        float new_x = game->player.pos.x + dx * step;
        float new_y = game->player.pos.y + dy * step;
        if (!is_wall(&game->map_info, new_x, new_y))
        {
            game->player.pos.x = new_x;
            game->player.pos.y = new_y;
        }
        minimap_render(game);
    }
    return (0);
}

int on_right_left(int keycode, t_game *game)
{
    if (keycode==123)
        rotate_player(&game->player, -M_PI/45);
    else if (keycode==124)
        rotate_player(&game->player, +M_PI/45);
    minimap_render(game);
    return (0);
}

int on_keypress(int keycode, t_game *game)
{
    printf("keycode: %d\n", keycode);
    if (keycode==123 || keycode==124)
        on_right_left(keycode, game);
    else if (keycode==13 || keycode==1 || keycode==0 || keycode == 2)
        on_wsad(keycode, game);
    else if (keycode==53)
        on_close(game);
    return (0);
}
