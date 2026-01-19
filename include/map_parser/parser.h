#ifndef PARSER_H
# define PARSER_H

# include "judge_data.h"
# include "map_builder.h"
# include "map_info.h"
# include "map_normalize_rectangle.h"
# include "map_scan_set_start.h"
# include "map_validate_closed.h"
# include "process_data.h"
# include "read_data.h"

int		flag_status_ok(const t_map_info *m);
int		parse_data(int fd, t_map_info *map_info);
void	ft_putstr_fd(char *str, int fd);

#endif
