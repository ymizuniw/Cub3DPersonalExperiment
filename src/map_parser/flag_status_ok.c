// #include "../../include/map_parser/map_info.h"
#include "../../include/map_parser/parser.h"
#include <stdbool.h>
#include <unistd.h>

int	flag_status_ok(const t_map_info *m)
{
	bool	err_items[COUNT];
	size_t	i;

	if (m == NULL)
	{
		ft_putstr_fd("map_info is null\n", 2);
		return (0);
	}
	i = 0;
	while (i < COUNT)
	{
		err_items[i] = 0;
		i++;
	}
	if (!m->flag_status.flag_status[NORTH])
		err_items[NORTH] = 1;
	if (!m->flag_status.flag_status[SOUTH])
		err_items[SOUTH] = 1;
	if (!m->flag_status.flag_status[WEST])
		err_items[WEST] = 1;
	if (!m->flag_status.flag_status[EAST])
		err_items[EAST] = 1;
	if (!m->flag_status.flag_status[FLOOR])
		err_items[FLOOR] = 1;
	if (!m->flag_status.flag_status[CEILING])
		err_items[CEILING] = 1;
	if (!m->flag_status.flag_status[START])
		err_items[START] = 1;
	if (!m->flag_status.flag_status[MAP])
		err_items[MAP] = 1;
	if (err_items[NORTH])
		ft_putstr_fd("NORTH: texture is not set.\n", 2);
	if (err_items[SOUTH])
		ft_putstr_fd("SOUTH: texture is not set\n", 2);
	if (err_items[WEST])
		ft_putstr_fd("WEST: texture is not set\n", 2);
	if (err_items[EAST])
		ft_putstr_fd("EAST: texture is not set\n", 2);
	if (err_items[FLOOR])
		ft_putstr_fd("FLOOR: color is not set\n", 2);
	if (err_items[CEILING])
		ft_putstr_fd("CEILING: color is not set\n", 2);
	if (err_items[START])
		ft_putstr_fd("START: start position/direction is not set\n", 2);
	if (err_items[MAP])
		ft_putstr_fd("MAP: map is not set\n", 2);
	i = 0;
	while (i < COUNT)
	{
		if (err_items[i])
			return (0);
		i++;
	}
	return (1);
}
