#include "../../include/core/game.h"

int	is_wall(const t_map_info *map_info, int x, int y)
{
	if (x < 0 || y < 0 || x >= map_info->map_cols || y >= map_info->map_rows)
		return (1);
	if (map_info->map[y * map_info->map_cols + x] == '1')
		return (1);
	return (0);
}
