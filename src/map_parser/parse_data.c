#include "../../include/map_parser/judge_data.h"
#include "../../include/map_parser/map_builder.h"
#include "../../include/map_parser/map_info.h"
#include "../../include/map_parser/map_normalize_rectangle.h"
#include "../../include/map_parser/parser.h"
#include "../../include/map_parser/read_data.h"
#include <stdio.h>
#include <stdlib.h>

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	except_map_flags_ok(bool *flag_status)
{
	if (flag_status[NORTH] && flag_status[SOUTH] && flag_status[EAST]
		&& flag_status[WEST] && flag_status[FLOOR] && flag_status[CEILING])
		return (1);
	return (0);
}

int	parse_data(int fd, t_map_info *map_info)
{
	t_read_status	read_status;
	t_read_line		read_line;
	char			*out_line;
	t_parse_phase	parse_phase;
	t_map_builder	mb;
	int				mb_initialized;
	t_judge_type	judge_type;
	int				process_texture_ret;
	int				process_color_ret;
	int				add_line_ret;
	size_t			saved_row_size;
	size_t			saved_col_size;
	char			**map;
	char			*rect_map;
	int				start_point[2];
	char			direction;
	int				scan_set_start_ret;
	int				validate_closed_ret;

	if (!map_info || fd < 0)
		return (-1);
	if (!read_line_init(&read_line, fd))
		return (-1);
	parse_phase = PHASE_ELEM;
	mb_initialized = 0;
	while (1)
	{
		read_status = read_next_line(&read_line, &out_line);
		if (read_status == RD_BAD_ARGS)
		{
			return (-1);
		}
		else if (read_status == RD_EOF)
		{
			break ;
		}
		judge_type = judge_line(out_line, parse_phase);
		if (parse_phase == PHASE_ELEM)
		{
			if (judge_type == J_EMPTY)
			{
				printf("type: J_EMPTY\nline: %s\n", out_line);
			}
			else if (judge_type == J_ELEM_NO)
			{
				printf("type: J_ELEM_NO\nline: %s\n", out_line);
				process_texture_ret = process_texture_line(map_info, judge_type,
						out_line);
				if (process_texture_ret < 0)
				{
					printf("process texture failed!\n");
					free(out_line);
					return (-1);
				}
				map_info->flag_status.flag_status[NORTH] = true;
			}
			else if (judge_type == J_ELEM_SO)
			{
				printf("type: J_ELEM_SO\nline: %s\n", out_line);
				process_texture_ret = process_texture_line(map_info, judge_type,
						out_line);
				if (process_texture_ret < 0)
				{
					ft_putstr_fd("process texture failed!\n", 2);
					free(out_line);
					return (-1);
				}
				map_info->flag_status.flag_status[SOUTH] = true;
			}
			else if (judge_type == J_ELEM_WE)
			{
				printf("type: J_ELEM_WE\nline: %s\n", out_line);
				process_texture_ret = process_texture_line(map_info, judge_type,
						out_line);
				if (process_texture_ret < 0)
				{
					ft_putstr_fd("process texture failed!\n", 2);
					free(out_line);
					return (-1);
				}
				map_info->flag_status.flag_status[WEST] = true;
			}
			else if (judge_type == J_ELEM_EA)
			{
				printf("type: J_ELEM_EA\nline: %s\n", out_line);
				process_texture_ret = process_texture_line(map_info, judge_type,
						out_line);
				if (process_texture_ret < 0)
				{
					ft_putstr_fd("process texture failed!\n", 2);
					free(out_line);
					return (-1);
				}
				map_info->flag_status.flag_status[EAST] = true;
			}
			else if (judge_type == J_ELEM_F)
			{
				printf("type: J_ELEM_F\nline: %s\n", out_line);
				process_color_ret = process_color_line(map_info, judge_type,
						out_line);
				if (process_color_ret < 0)
				{
					ft_putstr_fd("process color failed!\n", 2);
					free(out_line);
					return (-1);
				}
			}
			else if (judge_type == J_ELEM_C)
			{
				printf("type: J_ELEM_C\nline: %s\n", out_line);
				process_color_ret = process_color_line(map_info, judge_type,
						out_line);
				if (process_color_ret < 0)
				{
					ft_putstr_fd("process color failed!\n", 2);
					free(out_line);
					return (-1);
				}
			}
			else
			{
				printf("type: J_INVALID\nline: %s\n", out_line);
				free(out_line);
				return (-1);
			}
			if (except_map_flags_ok(map_info->flag_status.flag_status))
			{
				parse_phase = PHASE_MAP;
			}
		}
		else
		{
			if (judge_type == J_MAP_LINE)
			{
				printf("type: J_MAP_LINE\nline: %s\n", out_line);
				if (!mb_initialized)
				{
					map_builder_init(&mb);
					mb_initialized = 1;
				}
				add_line_ret = map_builder_add_line(&mb, out_line);
				if (add_line_ret < 0)
				{
					free(out_line);
					if (mb_initialized)
						map_builder_destroy(&mb);
					return (-1);
				}
			}
			else if (judge_type == J_EMPTY)
			{
				printf("type: J_EMPTY\nline: %s\n", out_line);
			}
			else
			{
				printf("type: J_INVALID\nline: %s\n", out_line);
				free(out_line);
				if (mb_initialized)
					map_builder_destroy(&mb);
				return (-1);
			}
		}
		free(out_line);
	}
	if (!mb_initialized)
	{
		ft_putstr_fd("No map data found!\n", 2);
		return (-1);
	}
	saved_row_size = mb.row_size;
	saved_col_size = mb.col_size;
	map = map_builder_return_map(&mb);
	if (map == NULL)
	{
		ft_putstr_fd("map_builder_return_map failed!\n", 2);
		return (-1);
	}
	rect_map = map_normalize_rectangle(map, saved_row_size, saved_col_size);
	if (rect_map == NULL)
	{
		ft_putstr_fd("map_normalize_rectangle failed!\n", 2);
		free_map(map);
		return (-1);
	}
	free_map(map);
	map_info->map = rect_map;
	map_info->map_rows = (int)saved_row_size;
	map_info->map_cols = (int)saved_col_size;
	start_point[0] = -1;
	start_point[1] = -1;
	scan_set_start_ret = map_scan_set_start(rect_map, saved_row_size,
			saved_col_size, start_point, &direction);
	if (scan_set_start_ret < 0)
	{
		ft_putstr_fd("scan_set_start failed!\n", 2);
		free(rect_map);
		return (-1);
	}
	map_info->flag_status.flag_status[START] = true;
	rect_map[start_point[0] * saved_col_size + start_point[1]] = '0';
	validate_closed_ret = map_validate_closed(rect_map, saved_row_size,
			saved_col_size, start_point[0], start_point[1]);
	if (validate_closed_ret != 1)
	{
		ft_putstr_fd("map has fault!\n", 2);
		free(rect_map);
		return (-1);
	}
	map_info->flag_status.flag_status[MAP] = true;
	map_info->start_x = start_point[1];
	map_info->start_y = start_point[0];
	map_info->start_direction = direction;
	if (flag_status_ok(map_info))
	{
		printf("flag_status_ok!\n");
		return (1);
	}
	return (-1);
}
