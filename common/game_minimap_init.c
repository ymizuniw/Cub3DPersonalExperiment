#include "includes/game.h"

void	game_minimap_init(t_game *game)
{
	game->mm.ox = 20;
	game->mm.oy = 20;
	game->mm.tile_size = 16;
}
