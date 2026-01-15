#include "map_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char	*judge_type_str(t_judge_type t)
{
	if (t == J_EMPTY)
		return ("J_EMPTY");
	if (t == J_ELEM_NO)
		return ("J_ELEM_NO");
	if (t == J_ELEM_SO)
		return ("J_ELEM_SO");
	if (t == J_ELEM_WE)
		return ("J_ELEM_WE");
	if (t == J_ELEM_EA)
		return ("J_ELEM_EA");
	if (t == J_ELEM_F)
		return ("J_ELEM_F");
	if (t == J_ELEM_C)
		return ("J_ELEM_C");
	if (t == J_MAP_LINE)
		return ("J_MAP_LINE");
	return ("J_INVALID");
}

static int	expect(const char *name, t_judge_type got, t_judge_type exp)
{
	if (got != exp)
	{
		printf("[KO] %s: got=%s exp=%s\n", name, judge_type_str(got),
			judge_type_str(exp));
		return (0);
	}
	printf("[OK] %s: %s\n", name, judge_type_str(got));
	return (1);
}

int	main(void)
{
	int	ok;

	ok = 1;
	ok &= expect("elem empty", judge_line("", PHASE_ELEM), J_EMPTY);
	ok &= expect("elem NO", judge_line("NO ./north.xpm", PHASE_ELEM),
			J_ELEM_NO);
	ok &= expect("elem SO", judge_line("SO ./south.xpm", PHASE_ELEM),
			J_ELEM_SO);
	ok &= expect("elem WE", judge_line("WE ./west.xpm", PHASE_ELEM), J_ELEM_WE);
	ok &= expect("elem EA", judge_line("EA ./east.xpm", PHASE_ELEM), J_ELEM_EA);
	ok &= expect("elem F", judge_line("F 220,100,0", PHASE_ELEM), J_ELEM_F);
	ok &= expect("elem C", judge_line("C 225,30,0", PHASE_ELEM), J_ELEM_C);
	ok &= expect("elem map start 1", judge_line("1111", PHASE_ELEM),
			J_MAP_LINE);
	ok &= expect("elem map start 2", judge_line("1 0N1", PHASE_ELEM),
			J_MAP_LINE);
	ok &= expect("elem invalid token", judge_line("XX ./x", PHASE_ELEM),
			J_INVALID);
	ok &= expect("elem invalid char in mapish", judge_line("11A1", PHASE_ELEM),
			J_INVALID);
	ok &= expect("map line", judge_line("1111", PHASE_MAP), J_MAP_LINE);
	ok &= expect("map line with spaces", judge_line("1 0 1", PHASE_MAP),
			J_MAP_LINE);
	ok &= expect("map invalid char", judge_line("10X1", PHASE_MAP), J_INVALID);
	ok &= expect("map empty", judge_line("", PHASE_MAP), J_EMPTY);
	if (!ok)
		return (1);
	return (0);
}