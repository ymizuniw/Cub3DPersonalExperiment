#ifndef JUDGE_DATA_H
# define JUDGE_DATA_H

typedef enum e_judge_type
{
	J_EMPTY,    // 空行 ""
	J_ELEM_NO,  // NO ./path
	J_ELEM_SO,  // SO ./path
	J_ELEM_WE,  // WE ./path
	J_ELEM_EA,  // EA ./path
	J_ELEM_F,   // F r,g,b
	J_ELEM_C,   // C r,g,b
	J_MAP_LINE, // マップ行
	J_INVALID   // 不正
}				t_judge_type;

typedef enum e_parse_phase
{
	PHASE_ELEM,
	PHASE_MAP
}				t_parse_phase;

t_judge_type	judge_line(const char *line, t_parse_phase phase);

#endif
