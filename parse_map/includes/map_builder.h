#ifndef MAP_BUILDER_H
# define MAP_BUILDER_H

# include <stddef.h>

typedef struct s_map_builder
{
	char	**lines;
	size_t	row_size;
	size_t	col_size;
}			t_map_builder;

void		map_builder_init(t_map_builder *b);
void		map_builder_destroy(t_map_builder *b);
int			map_builder_add_line(t_map_builder *b, const char *line);
char		**map_builder_return_map(t_map_builder *b);

#endif
