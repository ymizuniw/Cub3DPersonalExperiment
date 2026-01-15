#include "../includes/parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int			fd;
	t_map_info	info;
	int			ret;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	map_info_init(&info);
	printf("=== Testing parse_data with: %s ===\n", argv[1]);
	ret = parse_data(fd, &info);
	printf("\n=== Result: %d ===\n", ret);
	close(fd);
	map_info_destroy(&info);
	return (ret < 0 ? 1 : 0);
}
