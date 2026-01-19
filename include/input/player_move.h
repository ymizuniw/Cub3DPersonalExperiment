#ifndef PLAYER_MOVE_H
#define PLAYER_MOVE_H

#include "../core/game.h"

int	on_keypress(int keycode, t_game *game);
int	on_wsad(int keycode, t_game *game);
int	on_right_left(int keycode, t_game *game);

#endif
