#include "map_info.h"
#include "read_data.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int fd;
	t_read_line rl;
	char *line;
	t_read_status st;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	read_line_init(&rl, fd);
	while (1)
	{
		st = read_next_line(&rl, &line);
		if (st != RD_OK)
			break ;
		printf("[%zu]\"%s\"\n", rl.lineno, line);
		free(line);
	}
	if (st == RD_BAD_ARGS)
		fprintf(stderr, "read error\n");
	close(fd);
	return (0);
}