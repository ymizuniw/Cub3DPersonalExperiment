#include "../../common/includes/player.h"
#include "../../vector/includes/vec2.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPS 1e-4f

void	test_player_set_dir(void)
{
	t_player	player;

	printf("Testing player_set_dir...\n");
	// Test North
	player_set_dir(&player, 'N');
	assert(fabs(player.dir.x - 0.0f) < EPS);
	assert(fabs(player.dir.y - (-1.0f)) < EPS);
	// Test South
	player_set_dir(&player, 'S');
	assert(fabs(player.dir.x - 0.0f) < EPS);
	assert(fabs(player.dir.y - 1.0f) < EPS);
	// Test West
	player_set_dir(&player, 'W');
	assert(fabs(player.dir.x - (-1.0f)) < EPS);
	assert(fabs(player.dir.y - 0.0f) < EPS);
	// Test East
	player_set_dir(&player, 'E');
	assert(fabs(player.dir.x - 1.0f) < EPS);
	assert(fabs(player.dir.y - 0.0f) < EPS);
	printf("✓ player_set_dir tests passed\n");
}

void	test_rotate_player(void)
{
	t_player	player;

	printf("Testing rotate_player...\n");
	player.dir = init_v2(1.0, 0.0); // facing east
	// Rotate 90 degrees counter-clockwise (π/2)
	rotate_player(&player, M_PI / 2);
	assert(fabs(player.dir.x - 0.0f) < EPS);
	assert(fabs(player.dir.y - 1.0f) < EPS); // should face south
	// Rotate 90 degrees clockwise (-π/2) from east
	player.dir = init_v2(1.0, 0.0);
	rotate_player(&player, -M_PI / 2);
	assert(fabs(player.dir.x - 0.0f) < EPS);
	assert(fabs(player.dir.y - (-1.0f)) < EPS); // should face north
	// Small rotation test
	player.dir = init_v2(1.0, 0.0);
	rotate_player(&player, M_PI / 4); // 45 degrees
	assert(fabs(player.dir.x - cos(M_PI / 4)) < EPS);
	assert(fabs(player.dir.y - sin(M_PI / 4)) < EPS);
	printf("✓ rotate_player tests passed\n");
}

int	main(void)
{
	printf("Running player unit tests...\n\n");

	test_player_set_dir();
	test_rotate_player();

	printf("\n✓ All player tests passed!\n");
	return (0);
}