#include "../../include/map_parser/map_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	map_builder_init(t_map_builder *b)
{
	if (!b)
		return ;
	b->lines = NULL;
	b->row_size = 0;
	b->col_size = 0;
}

void	map_builder_destroy(t_map_builder *b)
{
	size_t	i;

	i = 0;
	if (!b)
		return ;
	while (i < b->row_size)
	{
		free(b->lines[i]);
		i++;
	}
	free(b->lines);
	b->lines = NULL;
	b->col_size = 0;
	b->row_size = 0;
}

static int	map_builder_add_slot(t_map_builder *b)
{
	char	**p;
	size_t	new_count;

	if (!b)
		return (-1);
	new_count = b->row_size + 2;
	p = (char **)malloc(new_count * sizeof(char *));
	if (!p)
		return (-1);
	if (b->lines && b->row_size > 0)
		memcpy(p, b->lines, b->row_size * sizeof(char *));
	p[b->row_size] = NULL;
	p[b->row_size + 1] = NULL;
	free(b->lines);
	b->lines = p;
	return (0);
}

int	map_builder_add_line(t_map_builder *b, const char *line)
{
	char	*dup;
	size_t	line_len;

	if (!b || !line)
		return (-1);
	dup = strdup(line);
	if (!dup)
		return (-1);
	if (map_builder_add_slot(b) < 0)
	{
		free(dup);
		return (-1);
	}
	b->lines[b->row_size++] = dup;
	b->lines[b->row_size] = NULL;
	line_len = strlen(dup);
	if (line_len > b->col_size)
		b->col_size = line_len;
	return (0);
}

char	**map_builder_return_map(t_map_builder *b)
{
	char	**out;

	if (!b || b->row_size == 0)
		return (NULL);
	out = b->lines;
	b->lines = NULL;
	b->row_size = 0;
	b->col_size = 0;
	return (out);
}
