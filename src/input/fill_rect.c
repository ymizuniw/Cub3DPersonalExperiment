#include "../../include/core/graphics.h"
#include <stdlib.h>

void	fill_rect(t_img *img, int x0, int y0, int w, int h, int color)
{
	int	x;
	int	y;

	y = y0;
	while (y < y0 + h)
	{
		x = x0;
		while (x < x0 + w)
		{
			ft_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
