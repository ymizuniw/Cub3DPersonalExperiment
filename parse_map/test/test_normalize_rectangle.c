#include "../includes/map_info.h"
#include "../includes/map_normalize_rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//cc -Wall -Wextra -Werror test_normalize_rectangle.c ../map_normalize_rectangle.c

static int expect_ok(const char *name, int cond)
{
    if (cond)
    {
        printf("[OK] %s\n", name);
        return (1);
    }
    printf("[KO] %s\n", name);
    return (0);
}

static int expect_cell(const char *name, const char *grid, int col_max, int r, int c, char exp)
{
    char got = grid[r*col_max + c];
    if (got == exp)
    {
        printf("[OK] %s\n", name);
        return (1);
    }
    printf("[KO] %s (r=%d c=%d got='%c' exp='%c')\n", name, r,c, got, exp);
    return (0);
}

static int expect_mem_eq(const char *name, const char *got, const char *exp, size_t n)
{
    if (memcmp(got, exp, n)==0)
    {
        printf("[OK] %s\n", name);
        return (1);
    }
    printf("[KO] %s (memcmp mismatch)\n", name);
    return (0);
}

int main(void)
{
    int ok = 1;

    //ragged rows, pad with spaces
    char *map[] = {"1111", "10 1", "10001", NULL};
    int row_max = 3;
    int col_max = 5;
    char *g = map_normalize_rectangle(map, row_max, col_max);
    ok &= expect_ok("case1 alloc", g != NULL);
    /*
        expected 3*5:
        "1111 "
        "10 1 "
        "10001"
    */
    ok &= expect_cell("case1 [0,4] pad space", g, col_max, 0,4, ' ');
    ok &= expect_cell("case1 [1,2] space kept", g, col_max, 1,2,' ');
    ok &= expect_cell("case1 [2,4] last char", g, col_max, 2,4,'1');
    {
        const char exp[] = {
            '1', '1', '1', '1', ' ',
            '1','0',' ','1',' ',
            '1','0','0','0','1'};
            ok &= expect_mem_eq("case1 full grid", g, exp, sizeof(exp));
    }
    free(g);
        /* Case 2: col_max shorter than some rows -> truncation */
    {
        char *map[] = { "ABCDE", "XYZ", NULL };
        int row_max = 2;
        int col_max = 3;

        char *g = map_normalize_rectangle(map, row_max, col_max);
        ok &= expect_ok("case2 alloc", g != NULL);

        /* expected 2x3:
           "ABC"
           "XYZ"
        */
        ok &= expect_cell("case2 [0,2] 'C'", g, col_max, 0, 2, 'C');
        ok &= expect_cell("case2 [1,2] 'Z'", g, col_max, 1, 2, 'Z');

        {
            const char exp[] = {'A','B','C','X','Y','Z'};
            ok &= expect_mem_eq("case2 full grid", g, exp, sizeof(exp));
        }

        free(g);
    }

    /* Case 3: empty strings */
    {
        char *map[] = { "", "", NULL };
        int row_max = 2;
        int col_max = 4;

        char *g = map_normalize_rectangle(map, row_max, col_max);
        ok &= expect_ok("case3 alloc", g != NULL);

        /* all spaces */
        for (int r = 0; r < row_max; r++)
            for (int c = 0; c < col_max; c++)
                ok &= expect_cell("case3 cell space", g, col_max, r, c, ' ');

        free(g);
    }

    /* Case 4: verify no hidden terminators (not NUL-terminated rows) */
    {
        char *map[] = { "1", NULL };
        int row_max = 1;
        int col_max = 2;

        char *g = map_normalize_rectangle(map, row_max, col_max);
        ok &= expect_ok("case4 alloc", g != NULL);
        ok &= expect_cell("case4 [0,0] '1'", g, col_max, 0, 0, '1');
        ok &= expect_cell("case4 [0,1] pad space", g, col_max, 0, 1, ' ');
        free(g);
    }

    return ok ? 0 : 1;
}
