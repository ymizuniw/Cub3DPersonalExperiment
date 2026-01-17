#!/bin/bash

cc test_rotate_player.c ../draw_player_dir.c ../rotate_player.c ../draw_line.c ../player_move.c ../player_set_dir.c ../clear_img.c ../fill_rect.c ../ft_put_pixel.c ../game_fn.c ../is_wall.c ../minimap_render.c\
  -I../includes \
  -I../../parse_map/includes \
  -I../../minilibx_opengl_20191021 \
  -L../../parse_map -lparse_map \
  -L../../minilibx_opengl_20191021 -lmlx \
  -framework OpenGL -framework AppKit
