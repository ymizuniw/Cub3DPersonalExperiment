#include "map_info.h"
#include <stdio.h>

static int	expect_ok(const char *name, int rc)
{
	if (rc == 0)
	{
		printf("[OK] %s\n", name);
		return (1);
	}
	printf("[KO] %s (expected OK)]\n", name);
	return (0);
}

static int	expect_ko(const char *name, int rc)
{
	if (rc != 0)
	{
		printf("[OK] %s\n", name);
		return (1);
	}
	printf("[KO] %s\n (expected KO)\n", name);
	return (0);
}

static int	expect_rgb(const char *name, int rgb[3], int r, int g, int b)
{
	if (rgb[0] == r && rgb[1] == g && rgb[2] == b)
	{
		printf("[OK] %s\n", name);
		return (1);
	}
	printf("[KO] %s (got=%d, %d, %d exp=%d,%d,%d)\n", name, rgb[0], rgb[1],
		rgb[2], r, g, b);
	return (0);
}

int	main(void)
{
	t_map_info	info;
	int			ok;
	t_map_info	tmp;

	ok = 1;
	map_info_init(&info);
	ok &= expect_ok("F basic", process_color_line(&info, J_ELEM_F,
				"F 220,100,0"));
	ok &= expect_rgb("F value", info.floor_color, 220, 100, 0);
	ok &= expect_ok("C spaces", process_color_line(&info, J_ELEM_C,
				"C 225,30,0  "));
	ok &= expect_rgb("C value", info.ceiling_color, 225, 30, 0);
	// irregular: duplication
	ok &= expect_ko("F duplicate", process_color_line(&info, J_ELEM_F,
				"F 0,0,0"));
	// irregular: lacking
	{
		map_info_init(&tmp);
		ok &= expect_ko("F missing value", process_color_line(&tmp, J_ELEM_F,
					"F "));
		map_info_destroy(&tmp);
	}
	// irregular: out of range
	{
		map_info_init(&tmp);
		ok &= expect_ko("C overflow", process_color_line(&tmp, J_ELEM_C,
					"C 256,0,0"));
		map_info_destroy(&tmp);
	}
	// irregular: format
	{
		map_info_init(&tmp);
		ok &= expect_ko("F bad format", process_color_line(&tmp, J_ELEM_F,
					"F 10,20"));
		map_info_destroy(&tmp);
	}
	// irregular: extra token
	{
		map_info_init(&tmp);
		ok &= expect_ko("C extra token", process_color_line(&tmp, J_ELEM_C,
					"C 1,2,3 extra"));
		map_info_destroy(&tmp);
	}
	map_info_destroy(&info);
	return (ok ? 0 : 1);
}
