// #include "includes/map_info.h"
#include "includes/read_data.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// the ownership of line is on caller side.
// call get_next_line()

int	read_line_init(t_read_line *rl, int fd)
{
	if (!rl || fd < 0)
		return (0);
	rl->fd = fd;
	rl->lineno = 0;
	return (1);
}

t_read_status	read_next_line(t_read_line *rl, char **out_line)
{
	char	*line;

	if (!rl || !out_line || rl->fd < 0)
		return (RD_BAD_ARGS);
	*out_line = NULL;
	line = get_next_line(rl->fd);
	if (!line)
		return (RD_EOF);
	rl->lineno++;
	*out_line = line;
	return (RD_OK);
}
