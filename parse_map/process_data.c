#include "map_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static const char	*skip_spaces(const char *s)
{
	while (s && *s && is_space(*s))
		s++;
	return (s);
}
static char	*dup_range(const char *start, const char *end)
{
	size_t	len;
	char	*p;

	if (!start || !end || end < start)
		return (NULL);
	len = (size_t)(end - start);
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	memcpy(p, start, len);
	p[len] = '\0';
	return (p);
}

static int	take_token(const char *s, const char **token_start,
		const char **token_end)
{
	const char	*p;

	if (!s || !token_start || !token_end)
		return (-1);
	p = skip_spaces(s);
	if (*p == '\0')
		return (-1);
	*token_start = p;
	while (*p && !is_space(*p))
		p++;
	*token_end = p;
	return (0);
}

static int	set_texture_field(char **texture_holder, bool *flag,
		const char *line_after_id)
{
	const char	*token_start;
	const char	*token_end;
	const char	*line_leftover;
	char		*path;

	if (!texture_holder || !flag || !line_after_id)
	{
		fprintf(stderr, "set_texture_field: data null\n");
		return (-1);
	}
	if (*flag)
	{
		fprintf(stderr, "set_texture_field: duplicate element\n");
		return (-1);
	}
	if (*line_after_id != ' ' && *line_after_id != '\t')
	{
		fprintf(stderr, "no separator between id and texture path\n");
		return (-1);
	}
	if (take_token(line_after_id, &token_start, &token_end) < 0)
	{
		fprintf(stderr, "set_texture_field: file path coudn't got\n");
		return (-1);
	}
	path = dup_range(token_start, token_end);
	if (!path)
	{
		fprintf(stderr, "set_texture_field: dup_range() failed\n");
		return (-1);
	}
	line_leftover = skip_spaces(token_end);
	if (*line_leftover != '\0')
	{
		fprintf(stderr, "set_texture_field: invalid format\n");
		free(path);
		return (-1);
	}
	*texture_holder = path;
	*flag = true;
	return (0);
}

int	process_texture_line(t_map_info *info, t_judge_type type, const char *line)
{
	if (!info || !line)
	{
		fprintf(stderr, "process_texture_line: argment null\n");
		return (-1);
	}
	if (type == J_ELEM_NO)
		return (set_texture_field(&info->north_texture,
				&info->flag_status.flag_status[NORTH], line + 2));
	if (type == J_ELEM_SO)
		return (set_texture_field(&info->south_texture,
				&info->flag_status.flag_status[SOUTH], line + 2));
	if (type == J_ELEM_WE)
		return (set_texture_field(&info->west_texture,
				&info->flag_status.flag_status[WEST], line + 2));
	if (type == J_ELEM_EA)
		return (set_texture_field(&info->east_texture,
				&info->flag_status.flag_status[EAST], line + 2));
	return (-1);
}

static int	ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
static int	parse_rgb_element(const char **str, int *value)
{
	int			tmp;
	const char	*s = *str;

	tmp = 0;
	if (!ft_isdigit(*s))
		return (-1);
	while (ft_isdigit(*s))
	{
		tmp = tmp * 10 + (*s - '0');
		if (tmp > 255)
			return (-1);
		s++;
	}
	*value = (int)tmp;
	*str = s;
	return (0);
}

static int	parse_rgb(const char *s, int rgb[3])
{
	s = skip_spaces(s);
	if (parse_rgb_element(&s, &rgb[0]) < 0)
		return (-1);
	if (*s++ != ',')
		return (-1);
	if (parse_rgb_element(&s, &rgb[1]) < 0)
		return (-1);
	if (*s++ != ',')
		return (-1);
	if (parse_rgb_element(&s, &rgb[2]) < 0)
		return (-1);
	s = skip_spaces(s);
	if (*s != '\0')
		return (-1);
	return (1);
}

int	process_color_line(t_map_info *info, t_judge_type type, const char *line)
{
	if (!info || !line)
		return (-1);
	if (type == J_ELEM_F)
	{
		if (info->flag_status.flag_status[FLOOR])
			return (-1);
		if (line[1] != ' ' && line[1] != '\t')
			return (-1);
		if (parse_rgb(line + 1, info->floor_color) < 0)
			return (-1);
		info->flag_status.flag_status[FLOOR] = true;
		return (0);
	}
	if (type == J_ELEM_C)
	{
		if (info->flag_status.flag_status[CEILING])
			return (-1);
		if (line[1] != ' ' && line[1] != '\t')
			return (-1);
		if (parse_rgb(line + 1, info->ceiling_color) < 0)
			return (-1);
		info->flag_status.flag_status[CEILING] = true;
		return (0);
	}
	return (-1);
}
