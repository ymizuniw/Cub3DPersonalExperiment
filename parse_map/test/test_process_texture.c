#include "map_info.h"
#include <stdio.h>
#include <string.h>

static int	expect_ok(const char *name, int rc)
{
	if (rc == 0)
	{
		printf("[OK] %s\n", name);
		return (1);
	}
	printf("[KO] %s (expected OK)\n", name);
	return (0);
}

static int	expect_ko(const char *name, int rc)
{
	if (rc != 0)
	{
		printf("[OK] %s\n", name);
		return (1);
	}
	printf("[KO] %s (expected KO)\n", name);
	return (0);
}

static int	expect_str(const char *name, const char *got, const char *exp)
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

int	main(void)
{
	t_map_info	info;
	int			ok;
	t_map_info	tmp;

	ok = 1;
	map_info_init(&info);
	ok &= expect_ok("NO basic", process_texture_line(&info, J_ELEM_NO,
				"NO ./north.xpm"));
	ok &= expect_str("NO stored path", info.north_texture, "./north.xpm");
	ok &= expect_ok("SO multi spaces", process_texture_line(&info, J_ELEM_SO,
				"SO    ./south.xpm   "));
	ok &= expect_str("SO stored path", info.south_texture, "./south.xpm");
	ok &= expect_ok("WE tab", process_texture_line(&info, J_ELEM_WE,
				"WE\t./west.xpm"));
	ok &= expect_str("WE stored path", info.west_texture, "./west.xpm");
	ok &= expect_ok("EA trailing spaces", process_texture_line(&info, J_ELEM_EA,
				"EA ./east.xpm   "));
	ok &= expect_str("EA stored path", info.east_texture, "./east.xpm");
	ok &= expect_ko("NO duplicate", process_texture_line(&info, J_ELEM_NO,
				"NO ./north2.xpm"));
	{
		map_info_init(&tmp);
		ok &= expect_ko("NO missing path", process_texture_line(&tmp, J_ELEM_NO,
					"NO "));
		map_info_destroy(&tmp);
	}
	{
		map_info_init(&tmp);
		ok &= expect_ko("SO extra token", process_texture_line(&tmp, J_ELEM_SO,
					"SO ./a.xpm extra"));
		map_info_destroy(&tmp);
	}
	{
		map_info_init(&tmp);
		ok &= expect_ko("WE no separator", process_texture_line(&tmp, J_ELEM_WE,
					"WE./a.xpm"));
		map_info_destroy(&tmp);
	}
	{
		map_info_init(&tmp);
		ok &= expect_ko("leading spaces (robustness)",
				process_texture_line(&tmp, J_ELEM_NO, " NO ./a.xpm"));
		map_info_destroy(&tmp);
	}
	map_info_destroy(&info);
	if (!ok)
		return (1);
	return (0);
}
