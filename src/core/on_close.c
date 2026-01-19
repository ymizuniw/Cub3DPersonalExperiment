#include "../../include/core/game.h"
#include "../../include/core/input.h"
#include <stdlib.h>

int	on_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game_destroy(game);
	exit(0);
	return (0);
}
