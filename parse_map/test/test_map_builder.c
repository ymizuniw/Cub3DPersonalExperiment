#include "map_builder.h"
#include "map_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	expect_ok(const char *name, int cond)
{
	if (cond)
	{
		printf("[OK] %s\n", name);
		return (1);
	}
	printf("[KO] %s\n", name);
	return (0);
}

static int	expect_streq(const char *name, const char *got, const char *exp)
{
	if (got && exp && strcmp(got, exp) == 0)
	{
		printf("[OK] %s\n", name);
		return (1);
	}
	printf("[KO] %s (got=\"%s\" exp=\"%s\")\n", name, got ? got : "(null)",
		exp ? exp : "(null)");
	return (0);
}

static void	free_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i++]);
	}
	free(map);
}

int	main(void)
{
	t_map_builder	b;
	int				ok;
	char			**map;

	ok = 1;
	map_builder_init(&b);
	ok &= expect_ok("init row_size==0", b.row_size == 0);
	ok &= expect_ok("init col_size==0", b.col_size == 0);
	ok &= expect_ok("init lines==NULL", b.lines == NULL);
	ok &= expect_ok("add line1 rc==0", map_builder_add_line(&b, "1111") == 0);
	ok &= expect_ok("row_size==1", b.row_size == 1);
	ok &= expect_ok("row_size==4", b.col_size == 4);
	ok &= expect_ok("lines[1]==NULL", b.lines && b.lines[1] == NULL);
	ok &= expect_streq("lines[0]==\"1111\"", b.lines[0], "1111");
	ok &= expect_ok("add line2 rc==0", map_builder_add_line(&b, "10 1") == 0);
	ok &= expect_ok("row_size==2", b.row_size == 2);
	ok &= expect_ok("col_size stays 4", b.col_size == 4);
	ok &= expect_ok("lines[2]==NULL", b.lines && b.lines[2] == NULL);
	ok &= expect_streq("lines[1]==\"10 1\"", b.lines[1], "10 1");
	ok &= expect_ok("add line3 rc==0", map_builder_add_line(&b, "10001") == 0);
	ok &= expect_ok("row_size==3", b.row_size == 3);
	ok &= expect_ok("col_size==5", b.col_size == 5);
	ok &= expect_ok("lines[3]==NULL", b.lines && b.lines[3] == NULL);
	ok &= expect_streq("lines[2]==\"10001\"", b.lines[2], "10001");
	map = map_builder_return_map(&b);
	ok &= expect_ok("return_map not NULL", map != NULL);
	ok &= expect_ok("builder emptied: lines==NULL", b.lines == NULL);
	ok &= expect_ok("builder emptied: row_size==0", b.row_size == 0);
	ok &= expect_ok("builder emptied: col_size==0", b.col_size == 0);
	ok &= expect_streq("map[0]==\"1111\"", map[0], "1111");
	ok &= expect_streq("map[1]==\"10 1\"", map[1], "10 1");
	ok &= expect_streq("map[2]==\"10001\"", map[2], "10001");
	ok &= expect_ok("map[3]==NULL", map[3] == NULL);
	free_map(map);
	map_builder_destroy(&b);
	ok &= expect_ok("destroy empty builder ok", 1);
	return (ok ? 0 : 1);
}
