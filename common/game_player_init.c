#include "includes/game.h"
#include "includes/player.h"

void	game_player_init(t_game *game)
{
	game->player.pos.x = game->map_info.start_x + 0.5f;
	game->player.pos.y = game->map_info.start_y + 0.5f;
	player_set_dir(&game->player, game->map_info.start_direction);
}
