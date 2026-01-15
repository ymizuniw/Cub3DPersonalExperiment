#ifndef MAP_INFO_H
# define MAP_INFO_H

# include "judge_data.h"
# include <stdbool.h>

typedef enum e_map_info_flags
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	START, // x,y,direction
	MAP,
	COUNT
}					t_map_info_flags;

typedef struct s_flag_status
{
	bool			flag_status[COUNT];
}					t_flag_status;

typedef struct s_map_info
{
	char			*map;
	int				map_rows;
	int				map_cols;
	int				start_x;
	int				start_y;
	char			start_direction;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	t_flag_status	flag_status;
}					t_map_info;

void				map_info_destroy(t_map_info *info);
void				map_info_init(t_map_info *info);
int					process_texture_line(t_map_info *info, t_judge_type type,
						const char *line);
int					process_color_line(t_map_info *info, t_judge_type type,
						const char *line);

#endif
