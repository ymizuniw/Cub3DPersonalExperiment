#include "../../include/core/graphics.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*p;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	p = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)p = (unsigned int)color;
}
