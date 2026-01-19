#include "../../common/includes/graphics.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void	test_ft_put_pixel(void)
{
	t_img	img;
	int		*pixel_ptr;

	printf("Testing ft_put_pixel...\n");
	// Create a simple test image
	img.w = 10;
	img.h = 10;
	img.bpp = 32;
	img.line_len = img.w * 4; // 4 bytes per pixel
	img.endian = 0;
	img.addr = malloc(img.h * img.line_len);
	// Clear image
	for (int i = 0; i < img.h * img.line_len; i++)
	{
		img.addr[i] = 0;
	}
	// Put a red pixel at (5, 5)
	ft_put_pixel(&img, 5, 5, 0xFF0000);
	// Check the pixel was set
	pixel_ptr = (int *)(img.addr + (5 * img.line_len + 5 * 4));
	assert(*pixel_ptr == 0xFF0000);
	// Test boundary conditions (should not crash)
	ft_put_pixel(&img, -1, 5, 0xFF0000); // out of bounds
	ft_put_pixel(&img, 15, 5, 0xFF0000); // out of bounds
	ft_put_pixel(&img, 5, -1, 0xFF0000); // out of bounds
	ft_put_pixel(&img, 5, 15, 0xFF0000); // out of bounds
	free(img.addr);
	printf("✓ ft_put_pixel tests passed\n");
}

void	test_clear_img(void)
{
	t_img	img;
	int		*pixel_ptr;

	printf("Testing clear_img...\n");
	// Create a test image
	img.w = 5;
	img.h = 5;
	img.bpp = 32;
	img.line_len = img.w * 4;
	img.endian = 0;
	img.addr = malloc(img.h * img.line_len);
	// Fill with some data first
	for (int i = 0; i < img.h * img.line_len / 4; i++)
	{
		((int *)img.addr)[i] = 0xFFFFFFFF;
	}
	// Clear with blue
	clear_img(&img, 0x0000FF);
	// Check all pixels are blue
	for (int y = 0; y < img.h; y++)
	{
		for (int x = 0; x < img.w; x++)
		{
			pixel_ptr = (int *)(img.addr + (y * img.line_len + x * 4));
			assert(*pixel_ptr == 0x0000FF);
		}
	}
	free(img.addr);
	printf("✓ clear_img tests passed\n");
}

void	test_fill_rect(void)
{
	t_img	img;
	int		*pixel_ptr;
	int		*corner_pixel;

	printf("Testing fill_rect...\n");
	// Create a test image
	img.w = 10;
	img.h = 10;
	img.bpp = 32;
	img.line_len = img.w * 4;
	img.endian = 0;
	img.addr = malloc(img.h * img.line_len);
	// Clear to black
	clear_img(&img, 0x000000);
	// Fill a 3x3 rectangle at (2,2) with red
	fill_rect(&img, 2, 2, 3, 3, 0xFF0000);
	// Check the rectangle was filled
	for (int y = 2; y < 5; y++)
	{
		for (int x = 2; x < 5; x++)
		{
			pixel_ptr = (int *)(img.addr + (y * img.line_len + x * 4));
			assert(*pixel_ptr == 0xFF0000);
		}
	}
	// Check outside rectangle is still black
	corner_pixel = (int *)(img.addr + (0 * img.line_len + 0 * 4));
	assert(*corner_pixel == 0x000000);
	free(img.addr);
	printf("✓ fill_rect tests passed\n");
}

void	test_draw_line(void)
{
	t_img	img;
	int		*pixel_ptr;
	int		*above_pixel;

	printf("Testing draw_line...\n");
	// Create a test image
	img.w = 10;
	img.h = 10;
	img.bpp = 32;
	img.line_len = img.w * 4;
	img.endian = 0;
	img.addr = malloc(img.h * img.line_len);
	// Clear to black
	clear_img(&img, 0x000000);
	// Draw a horizontal line from (2,2) to (7,2)
	draw_line(&img, 2, 2, 7, 2, 0xFF0000);
	// Check the line pixels
	for (int x = 2; x <= 7; x++)
	{
		pixel_ptr = (int *)(img.addr + (2 * img.line_len + x * 4));
		assert(*pixel_ptr == 0xFF0000);
	}
	// Check that adjacent pixels are still black
	above_pixel = (int *)(img.addr + (1 * img.line_len + 4 * 4));
	assert(*above_pixel == 0x000000);
	free(img.addr);
	printf("✓ draw_line tests passed\n");
}

int	main(void)
{
	printf("Running graphics unit tests...\n\n");

	test_ft_put_pixel();
	test_clear_img();
	test_fill_rect();
	test_draw_line();

	printf("\n✓ All graphics tests passed!\n");
	return (0);
}