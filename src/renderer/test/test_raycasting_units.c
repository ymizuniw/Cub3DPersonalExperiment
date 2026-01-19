#include "../../../raycasting.c"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPS 1e-4f

// Test data: 5x5 map with outer walls
char	test_map[] = "1111110001100011000111111";

void	setup_test_map_info(t_map_info *info)
{
	info->map = test_map;
	info->map_rows = 5;
	info->map_cols = 5;
}

void	test_decide_ray_dir(void)
{
	t_player	player;
	t_vec2		plane;
	t_ray		ray;
	int			screen_w;

	printf("Testing decide_ray_dir...\n");
	player.dir = init_v2(1, 0); // facing east
	plane = init_v2(0, 0.66);
	screen_w = 100;
	// Test x=0 (leftmost)
	decide_ray_dir(&ray, 0, screen_w, &plane, &player);
	assert(ray.dir.y < 0);                // should look upward (negative y)
	assert(fabs(ray.dir.x - 1.0f) < EPS); // x component should stay ~1
	// Test x=screen_w/2 (center)
	decide_ray_dir(&ray, screen_w / 2, screen_w, &plane, &player);
	assert(fabs(ray.dir.y) < EPS); // should look straight (y~0)
	assert(fabs(ray.dir.x - 1.0f) < EPS);
	// Test x=screen_w-1 (rightmost)
	decide_ray_dir(&ray, screen_w - 1, screen_w, &plane, &player);
	assert(ray.dir.y > 0); // should look downward (positive y)
	assert(fabs(ray.dir.x - 1.0f) < EPS);
	printf("✓ decide_ray_dir tests passed\n");
}

void	test_init_dda(void)
{
	t_player	player;
	t_ray		ray;
	t_dda		dda;

	printf("Testing init_dda...\n");
	player.pos = init_v2(2.5, 2.5);
	ray.dir = init_v2(1, 0.2);
	init_dda(&dda, &player, &ray);
	assert(dda.map_x == 2);
	assert(dda.map_y == 2);
	assert(fabs(dda.delta_dist_x - fabs(1.0 / ray.dir.x)) < EPS);
	assert(fabs(dda.delta_dist_y - fabs(1.0 / ray.dir.y)) < EPS);
	assert(dda.hit == 0);
	printf("✓ init_dda tests passed\n");
}

void	test_decide_step_dir(void)
{
	t_player	player;
	t_ray		ray_a;
	t_dda		dda_a;
	t_ray		ray_b;
	t_dda		dda_b;

	printf("Testing decide_step_dir...\n");
	player.pos = init_v2(2.5, 2.5);
	// Case A: ray.dir.x < 0, ray.dir.y > 0
	ray_a.pos = player.pos;
	ray_a.dir = init_v2(-0.5, 0.3);
	init_dda(&dda_a, &player, &ray_a);
	decide_step_dir(&ray_a, &dda_a);
	assert(dda_a.step_x == -1);
	assert(dda_a.step_y == 1);
	assert(fabs(dda_a.side_dist_x - (ray_a.pos.x - dda_a.map_x)
			* dda_a.delta_dist_x) < EPS);
	assert(fabs(dda_a.side_dist_y - (dda_a.map_y + 1 - ray_a.pos.y)
			* dda_a.delta_dist_y) < EPS);
	// Case B: ray.dir.x > 0, ray.dir.y < 0
	ray_b.pos = player.pos;
	ray_b.dir = init_v2(0.7, -0.4);
	init_dda(&dda_b, &player, &ray_b);
	decide_step_dir(&ray_b, &dda_b);
	assert(dda_b.step_x == 1);
	assert(dda_b.step_y == -1);
	assert(fabs(dda_b.side_dist_x - (dda_b.map_x + 1 - ray_b.pos.x)
			* dda_b.delta_dist_x) < EPS);
	assert(fabs(dda_b.side_dist_y - (ray_b.pos.y - dda_b.map_y)
			* dda_b.delta_dist_y) < EPS);
	printf("✓ decide_step_dir tests passed\n");
}

void	test_step_until_hit(void)
{
	t_map_info	map_info;
	t_player	player;
	t_ray		ray;
	t_dda		dda;

	printf("Testing step_until_hit...\n");
	setup_test_map_info(&map_info);
	player.pos = init_v2(2.5, 2.5); // center of map
	ray.pos = player.pos;
	ray.dir = init_v2(1, 0); // facing east
	init_dda(&dda, &player, &ray);
	decide_step_dir(&ray, &dda);
	step_until_hit(&dda, &map_info);
	assert(dda.hit != 0);
	assert(dda.map_x == 4); // should hit east wall
	assert(dda.side == 0);  // x-axis boundary
	printf("✓ step_until_hit tests passed\n");
}

void	test_seek_perp_dist(void)
{
	t_dda	dda;

	printf("Testing seek_perp_dist...\n");
	// Test side == 0
	dda.side = 0;
	dda.side_dist_x = 2.5;
	dda.delta_dist_x = 1.0;
	dda.side_dist_y = 3.0;
	dda.delta_dist_y = 1.5;
	seek_perp_dist(&dda);
	assert(fabs(dda.perp_dist - (dda.side_dist_x - dda.delta_dist_x)) < EPS);
	// Test side == 1
	dda.side = 1;
	seek_perp_dist(&dda);
	assert(fabs(dda.perp_dist - (dda.side_dist_y - dda.delta_dist_y)) < EPS);
	assert(dda.perp_dist > 0);
	printf("✓ seek_perp_dist tests passed\n");
}

void	test_decide_draw_ends(void)
{
	int	screen_h;
	int	close_height;
	int	far_height;

	printf("Testing decide_draw_ends...\n");
	int draw_start, draw_end;
	screen_h = 100;
	// Test close distance
	decide_draw_ends(&draw_start, &draw_end, screen_h, 1.0);
	close_height = draw_end - draw_start;
	// Test far distance
	decide_draw_ends(&draw_start, &draw_end, screen_h, 10.0);
	far_height = draw_end - draw_start;
	assert(close_height > far_height); // closer should be taller
	assert(draw_start >= 0);
	assert(draw_end < screen_h);
	assert(draw_start <= draw_end);
	printf("✓ decide_draw_ends tests passed\n");
}

void	test_decide_wall_dir(void)
{
	t_ray	ray;
	t_dda	dda;
	int		wall;

	printf("Testing decide_wall_dir...\n");
	// side==0, ray.dir.x > 0 -> EAST
	dda.side = 0;
	ray.dir = init_v2(1, 0);
	decide_wall_dir(&wall, &dda, &ray);
	assert(wall == EAST);
	// side==0, ray.dir.x < 0 -> WEST
	ray.dir = init_v2(-1, 0);
	decide_wall_dir(&wall, &dda, &ray);
	assert(wall == WEST);
	// side==1, ray.dir.y > 0 -> NORTH
	dda.side = 1;
	ray.dir = init_v2(0, 1);
	decide_wall_dir(&wall, &dda, &ray);
	assert(wall == NORTH);
	// side==1, ray.dir.y < 0 -> SOUTH
	ray.dir = init_v2(0, -1);
	decide_wall_dir(&wall, &dda, &ray);
	assert(wall == SOUTH);
	printf("✓ decide_wall_dir tests passed\n");
}

void	test_decide_wall_column(void)
{
	t_game	game;
	t_ray	ray;
	t_dda	dda;
	double	wall_x;
	double	expected_0;
	double	expected_1;

	printf("Testing decide_wall_column...\n");
	game.player.pos = init_v2(2.5, 2.5);
	ray.dir = init_v2(0.8, 0.6);
	dda.perp_dist = 1.3;
	// Test side == 0
	dda.side = 0;
	decide_wall_column(&wall_x, &dda, &ray, &game);
	expected_0 = game.player.pos.y + dda.perp_dist * ray.dir.y;
	assert(fabs(wall_x - expected_0) < EPS);
	// Test side == 1
	dda.side = 1;
	decide_wall_column(&wall_x, &dda, &ray, &game);
	expected_1 = game.player.pos.x + dda.perp_dist * ray.dir.x;
	assert(fabs(wall_x - expected_1) < EPS);
	printf("✓ decide_wall_column tests passed\n");
}

int	main(void)
{
	printf("Running raycasting unit tests...\n\n");
	test_decide_ray_dir();
	test_init_dda();
	test_decide_step_dir();
	test_step_until_hit();
	test_seek_perp_dist();
	test_decide_draw_ends();
	test_decide_wall_dir();
	test_decide_wall_column();
	printf("\n✓ All tests passed!\n");
	return (0);
}
