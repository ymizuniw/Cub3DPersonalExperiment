#ifndef IMAGE_H
#define IMAGE_H

typedef struct s_img
{
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int w;
    int h;
} t_img;

void ft_put_pixel(t_img *img, int x, int y, int color);
void clear_img(t_img *img, int color);

#endif
