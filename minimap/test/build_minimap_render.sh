#!/bin/bash

cc test_build_minimap_render.c ../../common/clear_img.c ../fill_rect.c ../../common/ft_put_pixel.c ../../common/game_mlx.c ../../common/game_player_init.c ../../common/game_minimap_init.c ../../common/game_lifecycle.c ../../common/on_close.c ../../common/player_set_dir.c ../is_wall.c ../minimap_render.c ../draw_player_dir.c ../draw_line.c ../../common/rotate_player.c\
  -I../includes \
  -I../../common/includes \
  -I../../parse_map/includes \
  -I../../vector/includes \
  -I../../minilibx_opengl_20191021 \
  -L../../parse_map -lparse_map \
  ../../vector/vector.a \
  -L../../minilibx_opengl_20191021 -lmlx \
  -framework OpenGL -framework AppKit \
  -lm
