#include "includes/game.h"
#include "includes/player.h"
#include <unistd.h>
#include <stdio.h>

int on_wsad(int keycode, t_game *game)
{
    float step = 0.10f;
    
    printf("keycode:%d\n", keycode);
    if (keycode == 13)
        game->player.y -= step;
    if (keycode == 1)
        game->player.y += step;
    if (keycode == 0)
        game->player.x -= step;
    if (keycode == 2)
        game->player.x += step;
    minimap_render(game);
    return (0);
}
