
#include "../../include/map_parser/parser.h"
#include <stdlib.h>

int	is_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	map_scan_set_start(char *map, int row_max, int col_max, int start[2],
		char *direction)
{
	int		i;
	int		j;
	bool	start_flag;

	i = 0;
	j = 0;
	start_flag = false;
	while (!(i == row_max && j == col_max))
	{
		j = 0;
		while (j < col_max)
		{
			if (is_direction(map[i * col_max + j]))
			{
				if (start_flag == false)
				{
					start[0] = i;
					start[1] = j;
					*direction = map[i * col_max + j];
					start_flag = true;
				}
				else
				{
					ft_putstr_fd("map_scan_set_start: multiple start point err\n",
						2);
					start[0] = -1;
					start[1] = -1;
					*direction = '?';
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	if (start_flag)
		return (1);
	ft_putstr_fd("map_scan_set_start: no start point found\n", 2);
	return (-1);
}
