#include "../minimap/includes/game.h"
#include "includes/ray.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_ray
{
	t_vec2	pos;
	t_vec2	dir;
}			t_ray;

typedef struct s_plane
{
	t_vec2	pos;
}			t_plane;

typedef struct s_dda
{
	// x-y boundary
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;

	// perpendicular distance between camera-plane and wall
	float	perp_dist;

	// map
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	char	side;

	// hit
	int		hit;
}			t_dda;

typedef struct s_fps
{
	float	time;
	float	old_time;
}			t_fps;

void	init_ray(t_ray *ray, const t_player *player)
{
	ray->pos = init_v2(player->pos.x, player->pos.y);
	ray->dir = init_v2(player->dir.x, player->dir.y);
}

void	init_plane(t_plane *plane, float const plane_x, float const plane_y)
{
	plane->pos = init_v2(plane_x, plane_y);
}

void	init_dda(t_dda *dda, const t_player *player, const t_ray *ray)
{
	dda->map_x = (int)player->pos.x;
	dda->map_y = (int)player->pos.y;
	dda->delta_dist_x = (ray->dir.x == 0) ? ULONG_MAX : fabs(1 / ray->dir.x);
	dda->delta_dist_y = (ray->dir.y == 0) ? ULONG_MAX : fabs(1 / ray->dir.y);
}

void	init_fps(t_fps *fps)
{
	fps->time = 0;
	fps->old_time = 0;
}

void	decide_step_dir_x(t_ray const *ray, t_dda *dda)
{
	if (ray->dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (ray->pos.x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0f - ray->pos.x) * dda->delta_dist_x;
	}
}

void	decide_step_dir_y(t_ray const *ray, t_dda *dda)
{
	if (ray->dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (ray->pos.y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0f - ray->pos.y) * dda->delta_dist_y;
	}
}

void	decide_step_dir(t_ray const *ray, t_dda *dda)
{
	decide_step_dir_x(ray, dda);
	decide_step_dir_y(ray, dda);
}

void	step_until_hit(t_dda *dda, t_map_info *map_info)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 'x';
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map_info->map[dda->map_y * map_info->map_cols + dda->map_x] == '1')
			dda->hit = 'y';
	}
}

void	seek_perp_dist(t_dda *dda)
{
	if (dda->side == 'x')
		dda->perp_dist = 0; // norm_v2(projection(hit_pos
							// - player.pos,normal_vec(plane));
	else
		dda->perp_dist = 0;
}

void	decide_ray_dir(t_ray *ray, int const x, int const map_rows,
		const t_plane *plane)
{
	float	camera_x;

	camera_x = 2 * x / (float)map_rows - 1;
	ray->dir.x = ray->dir.x + plane->pos.x * camera_x;
	ray->dir.y = ray->dir.y + plane->pos.y * camera_x;
}

int	raycasting(t_game *game)
{
	t_ray	ray;
	t_plane	plane;
	t_fps	fps;
	t_dda	dda;

	init_ray(&ray, &game->player);
	init_plane(&plane, 0, 0.66f);
	init_fps(&fps);
	while (!done())
	{
		for (int x = 0; x < game->map_info.map_rows; x++)
		{
			decide_ray_dir(&ray, x, game->map_info.map_rows, &plane);
			init_dda(&dda, &game->player, &ray);
			decide_step_dir(&ray, &dda);
			step_until_hit(&dda, &game->map_info);
			seek_perp_dist(&dda);
		}
	}
}
