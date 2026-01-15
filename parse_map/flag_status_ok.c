#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "includes/map_info.h"

int	flag_status_ok(const t_map_info *m)
{
	bool	err_items[COUNT];
	size_t	i;

	if (m == NULL)
	{
		printf("map_info is null\n");
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
		printf("NORTH: texture is not set.\n");
	if (err_items[SOUTH])
		printf("SOUTH: texture is not set\n");
	if (err_items[WEST])
		printf("WEST: texture is not set\n");
	if (err_items[EAST])
		printf("EAST: texture is not set\n");
	if (err_items[FLOOR])
		printf("FLOOR: color is not set\n");
	if (err_items[CEILING])
		printf("CEILING: color is not set\n");
	if (err_items[START])
		printf("START: start position/direction is not set\n");
	if (err_items[MAP])
		printf("MAP: map is not set\n");
	i = 0;
	while (i < COUNT)
	{
		if (err_items[i])
			return (0);
		i++;
	}
	return (1);
}
