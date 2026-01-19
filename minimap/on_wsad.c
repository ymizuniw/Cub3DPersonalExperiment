#include "../common/includes/game.h"
#include "../common/includes/player.h"
#include "includes/minimap_render.h"
#include "includes/player_move.h"

int	on_wsad(int keycode, t_game *game) {
  float step;
  float dx;
  float dy;
  float new_x;
  float new_y;

  step = 0.10f;
  dx = 0.0f;
  dy = 0.0f;
  if (keycode == 13)
    dy = -1.0f;
  if (keycode == 1)
    dy = 1.0f;
  if (keycode == 0)
    dx = -1.0f;
  if (keycode == 2)
    dx = 1.0f;
  if (dx != 0.0f || dy != 0.0f) {
    new_x = game->player.pos.x + dx * step;
    new_y = game->player.pos.y + dy * step;
    if (!is_wall(&game->map_info, new_x, new_y)) {
      game->player.pos.x = new_x;
      game->player.pos.y = new_y;
    }
    minimap_render(game);
  }
  return (0);
}
