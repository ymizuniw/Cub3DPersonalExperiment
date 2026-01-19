#include "../common/includes/game.h"
#include "../common/includes/player.h"
#include "includes/player_move.h"
#include <math.h>

int	on_right_left(int keycode, t_game *game)
{
	if (keycode == 123)
		rotate_player(&game->player, -M_PI / 45);
	else if (keycode == 124)
		rotate_player(&game->player, +M_PI / 45);
	return (0);
}
