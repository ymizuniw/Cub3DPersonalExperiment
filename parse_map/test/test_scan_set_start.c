#include <stdlib.h>
#include <stdbool.h>
#include "../includes/map_info.h"
#include "../includes/map_scan_set_start.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static int expect_rc(const char *name, int got, int exp)
{
    if (got == exp)
    {
        printf("[OK] %s\n", name);
        return 1;
    }
    printf("[KO] %s (got=%d exp=%d)\n", name, got, exp);
    return 0;
}

static int expect_xy(const char *name, int start[2], int x, int y)
{
    if (start[0] == x && start[1] == y)
    {
        printf("[OK] %s\n", name);
        return 1;
    }
    printf("[KO] %s (got=(%d,%d) exp=(%d,%d))\n",
           name, start[0], start[1], x, y);
    return 0;
}

static int expect_ch(const char *name, char got, char exp)
{
    if (got == exp)
    {
        printf("[OK] %s\n", name);
        return 1;
    }
    printf("[KO] %s (got='%c' exp='%c')\n", name, got, exp);
    return 0;
}

int main(void)
{
    int ok = 1;

    {
        char map[] =
            "1111 "
            "10N1 "
            "1111 ";
        int row_max = 3, col_max = 5;
        int start[2] = { -1, -1 };
        char dir = '?';

        int rc = map_scan_set_start(map, row_max, col_max, start, &dir);
        ok &= expect_rc("case1 rc==1", rc, 1);
        ok &= expect_xy("case1 start==(1,2)", start, 1, 2);
        ok &= expect_ch("case1 dir=='N'", dir, 'N');
    }

    {
        char map[] =
            "E111"
            "1001"
            "1111";
        int row_max = 3, col_max = 4;
        int start[2] = { -1, -1 };
        char dir = '?';

        int rc = map_scan_set_start(map, row_max, col_max, start, &dir);
        ok &= expect_rc("case2 rc==1", rc, 1);
        ok &= expect_xy("case2 start==(0,0)", start, 0, 0);
        ok &= expect_ch("case2 dir=='E'", dir, 'E');
    }

    {
        char map[] =
            "1111"
            "1N01"
            "1S11";
        int row_max = 3, col_max = 4;
        int start[2] = { -1, -1 };
        char dir = '?';

        int rc = map_scan_set_start(map, row_max, col_max, start, &dir);
        ok &= expect_rc("case3 rc==-1", rc, -1);
    }

    {
        char map[] =
            "111"
            "101"
            "111";
        int row_max = 3, col_max = 3;
        int start[2] = { -1, -1 };
        char dir = '?';

        int rc = map_scan_set_start(map, row_max, col_max, start, &dir);
        ok &= expect_rc("case4 rc==-1", rc, -1);
        ok &= expect_xy("case4 start stays (-1,-1)", start, -1, -1);
        ok &= expect_ch("case4 dir stays '?'", dir, '?');
    }

    return ok ? 0 : 1;
}

