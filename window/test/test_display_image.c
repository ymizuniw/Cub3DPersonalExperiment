#include <mlx.h>

// cc test_display_image.c -I ../minilibx_opengl_20191021/ -L ../minilibx_opengl_20191021/  -lmlx -framework OpenGL -framework AppKit

int main(void)
{
    void *img;
    char *relative_path = "../data/sample.xpm";
    int img_width;
    int img_height;
    void *mlx = mlx_init();
    if (!mlx)
        return (1);
    void *win;
    win = mlx_new_window(mlx, 640, 480, "mlx ok");
    if (!win)
        return (1);
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
    return (0);
}
