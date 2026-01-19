#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "image.h"

// Forward declaration to avoid circular dependency
typedef struct s_game	t_game;

void					ft_put_pixel(t_img *img, int x, int y, int color);
void					clear_img(t_img *img, int color);
void					draw_line(t_img *img, int x0, int y0, int x1, int y1,
							int color);
void					fill_rect(t_img *img, int x0, int y0, int w, int h,
							int color);
#endif
