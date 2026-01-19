#ifndef RAY_H
# define RAY_H

# include "../../vector/includes/vec2.h"

typedef struct s_ray
{
	t_vec2	pos;
	t_vec2	dir;
	float	angle;
}			t_ray;

typedef struct s_plane
{
	t_vec2	pos;
}			t_plane;

typedef struct s_dda
{
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;

	float	perp_dist;

	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;

	int		hit;
}			t_dda;

typedef struct s_fps
{
	float	time;
	float	old_time;
}			t_fps;

#endif
