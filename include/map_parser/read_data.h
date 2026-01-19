#ifndef READ_DATA_H
# define READ_DATA_H

# include <stddef.h>

typedef enum e_read_status
{
	RD_OK = 1,
	RD_EOF = 0,
	RD_BAD_ARGS = -1
}				t_read_status;

typedef struct s_read_line
{
	int			fd;
	size_t		lineno;
}				t_read_line;

int				read_line_init(t_read_line *rl, int fd);
t_read_status	read_next_line(t_read_line *rl, char **out_line);

char			*get_next_line(int fd);

#endif
