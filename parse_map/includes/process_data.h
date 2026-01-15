#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include "map_info.h"

int	process_texture_line(t_map_info *info, t_judge_type type, const char *line);
int	process_color_line(t_map_info *info, t_judge_type type, const char *line);

#endif
