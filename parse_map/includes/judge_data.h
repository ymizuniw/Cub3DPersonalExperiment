#ifndef JUDGE_DATA_H
# define JUDGE_DATA_H

typedef enum e_judge_type
{
	J_EMPTY,
	J_ELEM_NO,
	J_ELEM_SO,
	J_ELEM_WE,
	J_ELEM_EA,
	J_ELEM_F,
	J_ELEM_C,
	J_MAP_LINE,
	J_INVALID
}				t_judge_type;

typedef enum e_parse_phase
{
	PHASE_ELEM,
	PHASE_MAP
}				t_parse_phase;

t_judge_type	judge_line(const char *line, t_parse_phase phase);

#endif
