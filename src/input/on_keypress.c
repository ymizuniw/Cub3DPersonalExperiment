#include "../../include/core/game.h"
#include "../../include/core/input.h"
#include "player_move.h"
#include <stdio.h>

int	on_keypress(int keycode, t_game *game)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 123 || keycode == 124)
		on_right_left(keycode, game);
	else if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
		on_wsad(keycode, game);
	else if (keycode == 53)
		on_close(game);
	return (0);
}
