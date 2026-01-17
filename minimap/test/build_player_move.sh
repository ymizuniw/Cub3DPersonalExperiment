#!/bin/bash

cc test_player_move.c ../player_move.c ../clear_img.c ../fill_rect.c ../ft_put_pixel.c ../game_fn.c ../is_wall.c ../minimap_render.c\
  -I../includes \
  -I../../parse_map/includes \
  -I../../minilibx_opengl_20191021 \
  -L../../parse_map -lparse_map \
  -L../../minilibx_opengl_20191021 -lmlx \
  -framework OpenGL -framework AppKit
