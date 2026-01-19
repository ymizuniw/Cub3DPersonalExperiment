#include "../../include/core/game.h"
#include "../../include/core/graphics.h"
#include "../../include/core/ray.h"
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	init_ray(t_ray *ray, const t_player *player)
{
	ray->pos = init_v2(player->pos.x, player->pos.y);
	ray->dir = init_v2(player->dir.x, player->dir.y);
	ray->angle = 0.f;
}

void	init_plane(t_plane *plane, float const plane_x, float const plane_y)
{
	plane->pos = init_v2(plane_x, plane_y);
}

void	init_dda(t_dda *dda, const t_player *player, const t_ray *ray)
{
	dda->map_x = (int)player->pos.x;
	dda->map_y = (int)player->pos.y;
	if (fabs(ray->dir.x) < 1e-9f)
		dda->delta_dist_x = FLT_MAX;
	else
		dda->delta_dist_x = fabs(1.0f / ray->dir.x);
	if (fabs(ray->dir.y) < 1e-9f)
		dda->delta_dist_y = FLT_MAX;
	else
		dda->delta_dist_y = fabs(1.0f / ray->dir.y);
	dda->hit = 0;
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
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map_info->map[dda->map_y * map_info->map_cols + dda->map_x] == '1')
			dda->hit = 1;
	}
}

void	seek_perp_dist(t_dda *dda)
{
	if (dda->side == 0)
		dda->perp_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->perp_dist = dda->side_dist_y - dda->delta_dist_y;
}

void	decide_ray_dir(t_ray *ray, int const x, int const screen_w,
		const t_vec2 *plane, const t_player *player)
{
	float	camera_x;

	ray->dir.x = player->dir.x;
	ray->dir.y = player->dir.y;
	camera_x = 2 * x / (float)screen_w - 1;
	ray->dir.x = ray->dir.x + plane->x * camera_x;
	ray->dir.y = ray->dir.y + plane->y * camera_x;
}

void	decide_draw_ends(int *draw_start, int *draw_end, int frame_height,
		float perp_dist)
{
	int	line_height;

	if (perp_dist < 1e-6f)
		perp_dist = 1e-6f;
	line_height = (int)(frame_height / perp_dist);
	if (line_height > frame_height * 10)
		line_height = frame_height * 10;
	*draw_start = -line_height / 2 + frame_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + frame_height / 2;
	if (*draw_end >= frame_height)
		*draw_end = frame_height - 1;
}

void	decide_wall_dir(int *wall, t_dda const *dda, t_ray const *ray)
{
	if (dda->side == 0)
	{
		if (ray->dir.x > 0)
			*wall = EAST;
		else
			*wall = WEST;
	}
	else
	{
		if (ray->dir.y > 0)
			*wall = NORTH;
		else
			*wall = SOUTH;
	}
}

void	decide_wall_column(double *wall_col, t_dda const *dda, t_ray const *ray,
		t_game const *game)
{
	if (dda->side == 0)
		*wall_col = game->player.pos.y + dda->perp_dist * ray->dir.y;
	else
		*wall_col = game->player.pos.x + dda->perp_dist * ray->dir.x;
}

typedef struct s_draw_ctx
{
	int		x;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	wall_x;
	int		side;
	int		texture_id;
}			t_draw_ctx;

void	init_draw_ctx(t_draw_ctx *dc)
{
	memset(dc, 0, sizeof(t_draw_ctx));
}

void	draw_to_frame_buffer(t_game *game, t_draw_ctx const *dc)
{
	int	color;
	int	y;

	if (dc->side == 0)
	{
		if (dc->texture_id == NORTH)
			color = 0xFF0000;
		else
			color = 0x800000;
	}
	else
	{
		if (dc->texture_id == EAST)
			color = 0x00FF00;
		else
			color = 0x008000;
	}
	for (y = dc->draw_start; y <= dc->draw_end; y++)
	{
		ft_put_pixel(&game->frame, dc->x, y, color);
	}
}

int	raycasting(t_game *game)
{
	t_ray		ray;
	t_fps		fps;
	t_dda		dda;
	t_draw_ctx	dc;

	init_ray(&ray, &game->player);
	init_fps(&fps);
	init_draw_ctx(&dc);
	for (int x = 0; x < game->frame.w; x++)
	{
		dc.x = x;
		decide_ray_dir(&ray, x, game->frame.w, &game->player.plane,
			&game->player);
		init_dda(&dda, &game->player, &ray);
		decide_step_dir(&ray, &dda);
		step_until_hit(&dda, &game->map_info);
		seek_perp_dist(&dda);
		dc.side = dda.side;
		decide_draw_ends(&dc.draw_start, &dc.draw_end, game->frame.h,
			dda.perp_dist);
		decide_wall_dir(&dc.texture_id, &dda, &ray);
		decide_wall_column(&dc.wall_x, &dda, &ray, game);
		draw_to_frame_buffer(game, &dc);
	}
	return (0);
}
