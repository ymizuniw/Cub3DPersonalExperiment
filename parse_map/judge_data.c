#include "includes/map_info.h"
#include <stdio.h>
#include <string.h>

static int	is_empty_line(char const *line)
{
	return (!line || *line == '\0');
}

static int	is_map_charset(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

t_judge_type	judge_line(const char *line, t_parse_phase phase)
{
	size_t	i;

	if (!line)
		return (J_INVALID);
	if (is_empty_line(line))
		return (J_EMPTY);
	if (phase == PHASE_ELEM)
	{
		if (strncmp(line, "NO", 2) == 0)
			return (J_ELEM_NO);
		if (strncmp(line, "SO", 2) == 0)
			return (J_ELEM_SO);
		if (strncmp(line, "WE", 2) == 0)
			return (J_ELEM_WE);
		if (strncmp(line, "EA", 2) == 0)
			return (J_ELEM_EA);
		if (strncmp(line, "F", 1) == 0)
			return (J_ELEM_F);
		if (strncmp(line, "C", 1) == 0)
			return (J_ELEM_C);
	}
	i = 0;
	while (line[i])
	{
		if (!is_map_charset(line[i]))
		{
			return (J_INVALID);
		}
		i++;
	}
	return (J_MAP_LINE);
}
