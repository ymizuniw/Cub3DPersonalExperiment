#include "../../include/core/graphics.h"
#include "../../include/core/image.h"

int	abs_int(int val)
{
	if (val < 0)
		return (-val);
	else
		return (val);
}

void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int		dy;
	int		dx;
	int		sign_x;
	int		sign_y;
	char	main_axis;
	int		err;

	dy = abs_int(y1 - y0);
	dx = abs_int(x1 - x0);
	if (x1 - x0 < 0)
		sign_x = -1;
	else
		sign_x = 1;
	if (y1 - y0 < 0)
		sign_y = -1;
	else
		sign_y = 1;
	if (dx < dy)
		main_axis = 'y';
	else
		main_axis = 'x';
	if (main_axis == 'x')
	{
		err = -dx;
		while (x0 != x1)
		{
			ft_put_pixel(img, x0, y0, color);
			x0 += sign_x;
			err += 2 * dy;
			if (err >= 0)
			{
				y0 += sign_y;
				err -= 2 * dx;
			}
		}
	}
	else
	{
		err = -dy;
		while (y0 != y1)
		{
			ft_put_pixel(img, x0, y0, color);
			y0 += sign_y;
			err += 2 * (dx);
			if (err >= 0)
			{
				x0 += sign_x;
				err -= 2 * (dy);
			}
		}
	}
	ft_put_pixel(img, x1, y1, color);
}
