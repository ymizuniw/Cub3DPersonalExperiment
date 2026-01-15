#include "../includes/map_validate_closed.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int expect_rc(const char *name, int got, int exp)
{
	if (got == exp) { printf("[OK] %s\n", name); return 1; }
	printf("[KO] %s (got=%d exp=%d)\n", name, got, exp);
	return 0;
}

static void copy_grid(char *dst, const char *src, size_t n)
{
	memcpy(dst, src, n);
}

int main(void)
{
	int ok = 1;

	{
		const int H = 3, W = 4;
		const char src[] =
			"1111"
			"1001"
			"1111";
		char map[3 * 4];

		copy_grid(map, src, sizeof(map));
		ok &= expect_rc("closed basic -> 1", map_validate_closed(map, H, W, 1, 1), 1);
	}

	{
		const int H = 3, W = 4;
		const char src[] =
			"1111"
			"1000" /* border col=3 is '0' */
			"1111";
		char map[3 * 4];

		copy_grid(map, src, sizeof(map));
		ok &= expect_rc("open border 0 -> -1", map_validate_closed(map, H, W, 1, 1), -1);
	}

	{
		const int H = 3, W = 5;
		const char src[] =
			"11111"
			"10 01"
			"11111";
		char map[3 * 5];

		copy_grid(map, src, sizeof(map));
		ok &= expect_rc("space reachable -> -1", map_validate_closed(map, H, W, 1, 1), -1);
	}

	{
		const int H = 4, W = 5;
		const char src[] =
			"11111"
			"10111"
			"10001"
			"11111";
		char map[4 * 5];

		copy_grid(map, src, sizeof(map));
		ok &= expect_rc("near border closed -> 1", map_validate_closed(map, H, W, 1, 1), 1);
	}

{
    const int H = 5, W = 5;
    const char src[] =
        "11111"
		"10000"  /* 右端 col=4 が '0'（境界）かつ start(1,1) から到達可能 */
        "11111"
        "11111"
        "11111";
    char map[5 * 5];

    copy_grid(map, src, sizeof(map));
    ok &= expect_rc("corridor to border 0 -> -1", map_validate_closed(map, H, W, 1, 1), -1);
}


	return ok ? 0 : 1;
}
