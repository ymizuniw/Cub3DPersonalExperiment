#include <stdlib.h>
#include "../minilibx_opengl_20191021/mlx.h"

// cc test_mlx_open.c -I ../minilibx_opengl_20191021/ -L ../minilibx_opengl_20191021/  -lmlx -framework OpenGL -framework AppKit

int main(void)
{
    void *mlx = mlx_init();
    void *win;

    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, 640, 480, "mlx ok");
    if (!win)
        return (1);
    mlx_loop(mlx);
    return (0);
}
