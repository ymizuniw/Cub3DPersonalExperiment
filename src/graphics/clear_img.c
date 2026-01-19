#include "graphics.h"
#include <stdlib.h>

void clear_img(t_img *img, int color)
{
    int x;
    int y;

    y = 0;
    while(y<img->h)
    {
        x=0;
        while(x<img->w)
        {
            ft_put_pixel(img, x, y, color);
            x++;
        }
        y++;
    }
}
