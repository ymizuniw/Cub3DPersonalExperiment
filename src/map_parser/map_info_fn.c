#include "map_info.h"
#include <stdlib.h>
#include <string.h>

void	map_info_init(t_map_info *info)
{
	size_t	i;

	i = 0;
	if (!info)
		return ;
	memset(info, 0, sizeof(*info));
	while (i < COUNT)
	{
		info->flag_status.flag_status[i] = false;
		i++;
	}
}

void	map_info_destroy(t_map_info *info)
{
	if (!info)
		return ;
	if (info->north_texture)
		free(info->north_texture);
	if (info->south_texture)
		free(info->south_texture);
	if (info->west_texture)
		free(info->west_texture);
	if (info->east_texture)
		free(info->east_texture);
	if (info->map)
		free(info->map);
	info->north_texture = NULL;
	info->south_texture = NULL;
	info->west_texture = NULL;
	info->east_texture = NULL;
	info->map = NULL;
}
