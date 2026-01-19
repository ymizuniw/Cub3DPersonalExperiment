#ifndef MINIMAP_RENDER_H
# define MINIMAP_RENDER_H

# include "../core/game.h"
# include "../core/graphics.h"
# include "../map_parser/map_info.h"

void	minimap_render(t_game *game);
void	draw_player_dir(t_game *game);
int		is_wall(const t_map_info *map_info, int x, int y);

#endif
