#include "../../../common/includes/game.h"
#include "../../includes/minimap_render.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple test map: 3x3 with walls around edges
char	test_map[] = "111101111";

void	setup_test_map_info(t_map_info *info)
{
	info->map = test_map;
	info->map_rows = 3;
	info->map_cols = 3;
}

void	test_is_wall(void)
{
	t_map_info	map_info;

	printf("Testing is_wall...\n");
	setup_test_map_info(&map_info);
	// Test wall positions
	assert(is_wall(&map_info, 0, 0) == 1); // top-left corner
	assert(is_wall(&map_info, 2, 0) == 1); // top-right corner
	assert(is_wall(&map_info, 0, 2) == 1); // bottom-left corner
	assert(is_wall(&map_info, 2, 2) == 1); // bottom-right corner
	// Test non-wall position
	assert(is_wall(&map_info, 1, 1) == 0); // center should be open
	// Test out-of-bounds (should be treated as wall)
	assert(is_wall(&map_info, -1, 0) == 1);
	assert(is_wall(&map_info, 3, 0) == 1);
	assert(is_wall(&map_info, 0, -1) == 1);
	assert(is_wall(&map_info, 0, 3) == 1);
	printf("✓ is_wall tests passed\n");
}

int	main(void)
{
	printf("Running minimap unit tests...\n\n");

	test_is_wall();

	printf("\n✓ All minimap tests passed!\n");
	return (0);
}