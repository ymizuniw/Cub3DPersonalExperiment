#include "../includes/parser.h"
#include "../includes/judge_data.h"
#include "../includes/read_data.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_test_result
{
	int		total_lines;
	int		empty_count;
	int		elem_count;
	int		map_count;
	int		invalid_count;
	int		phase_changed;
}	t_test_result;

static void	print_test_result(const char *filename, t_test_result *res)
{
	printf("\n=== Summary for %s ===\n", filename);
	printf("Total lines: %d\n", res->total_lines);
	printf("Empty lines: %d\n", res->empty_count);
	printf("Element lines: %d\n", res->elem_count);
	printf("Map lines: %d\n", res->map_count);
	printf("Invalid lines: %d\n", res->invalid_count);
	printf("Phase changed to MAP: %s\n", res->phase_changed ? "YES" : "NO");
}

int	test_parse_types(int fd, const char *filename)
{
	t_read_line		rl;
	t_read_status	st;
	t_parse_phase	phase;
	char			*line;
	t_judge_type	type;
	t_test_result	res;

	memset(&res, 0, sizeof(res));
	if (!read_line_init(&rl, fd))
	{
		fprintf(stderr, "Error: read_line_init failed\n");
		return (-1);
	}
	phase = PHASE_ELEM;
	printf("=== Testing type judgment: %s ===\n", filename);
	while (1)
	{
		st = read_next_line(&rl, &line);
		if (st == RD_EOF)
			break ;
		if (st == RD_BAD_ARGS)
		{
			fprintf(stderr, "Error: read_next_line failed\n");
			return (-1);
		}
		type = judge_line(line, phase);
		res.total_lines++;
		printf("[%zu] ", rl.lineno);
		if (type == J_EMPTY)
		{
			printf("J_EMPTY: \"%s\"\n", line);
			res.empty_count++;
		}
		else if (type == J_ELEM_NO)
		{
			printf("J_ELEM_NO: \"%s\"\n", line);
			res.elem_count++;
		}
		else if (type == J_ELEM_SO)
		{
			printf("J_ELEM_SO: \"%s\"\n", line);
			res.elem_count++;
		}
		else if (type == J_ELEM_WE)
		{
			printf("J_ELEM_WE: \"%s\"\n", line);
			res.elem_count++;
		}
		else if (type == J_ELEM_EA)
		{
			printf("J_ELEM_EA: \"%s\"\n", line);
			res.elem_count++;
		}
		else if (type == J_ELEM_F)
		{
			printf("J_ELEM_F: \"%s\"\n", line);
			res.elem_count++;
		}
		else if (type == J_ELEM_C)
		{
			printf("J_ELEM_C: \"%s\"\n", line);
			res.elem_count++;
		}
		else if (type == J_MAP_LINE)
		{
			printf("J_MAP_LINE: \"%s\"\n", line);
			res.map_count++;
			if (phase == PHASE_ELEM)
			{
				phase = PHASE_MAP;
				res.phase_changed = 1;
				printf("  -> Phase changed to PHASE_MAP\n");
			}
		}
		else
		{
			printf("J_INVALID: \"%s\"\n", line);
			res.invalid_count++;
		}
		free(line);
	}
	print_test_result(filename, &res);
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;
	int	ret;

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
	ret = test_parse_types(fd, argv[1]);
	close(fd);
	return (ret < 0 ? 1 : 0);
}
