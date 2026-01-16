#include <mlx.h>

//0,1,' '

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

void ft_put_pixel(t_data *data, int x, int y, int color)
{
    char *pxl;

    if (x>=0 && x < WINDOW_WIDTH && y >= 0 && y< WINDOW_HEIGHT)
    {
        pxl = data->addr + (y*data->line_length + x * (data->bits_per_pixel/8));
        *(unsigned int *)pxl = color;
    }
}

static inline void swap_int(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void draw_horizontal_line(t_data *data, int x0, int x1, int y, int color)
{
    int x;
    if (x0 > x1)
        swap_int(&x0, &x1);
    x = x0;
    while(x<=x1)
    {
        ft_put_pixel(data, x, y, color);
        x++;
    }
}

void draw_vertical_line(t_data *data, int x, int y0, int y1, int color)
{
    int y;
    if (y0 > y1)
        swap_int(&y0, &y1);
    y = y0;
    while (y <= y1)
    {
        ft_put_pixel(data, x, y, color);
        y++;
    }
}

void draw_rect(t_data *img,
               int x0, int y0,
               int x1, int y1,
               int color)
{
    draw_horizontal_line(img, x0, x1, y0, color); // 上
    draw_horizontal_line(img, x0, x1, y1, color); // 下
    draw_vertical_line(img, x0, y0, y1, color);   // 左
    draw_vertical_line(img, x1, y0, y1, color);   // 右
}


int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 900, 900, "display1");
    img.img = mlx_new_image(mlx, 900, 900);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,&img.line_length, &img.endian);
    ft_put_pixel(&img, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0xFF0000);
    draw_rect(&img, 200,200,700,700,0x00FF00);
    mlx_put_image_to_window(mlx,mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
    return (0);
}
