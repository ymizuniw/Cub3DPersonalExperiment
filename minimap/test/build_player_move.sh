#!/bin/bash

cc test_player_move.c ../on_keypress.c ../on_wsad.c ../on_right_left.c ../../common/player_set_dir.c ../draw_player_dir.c ../../common/rotate_player.c ../draw_line.c ../../common/clear_img.c ../fill_rect.c ../../common/ft_put_pixel.c ../../common/game_mlx.c ../../common/game_player_init.c ../../common/game_minimap_init.c ../../common/game_lifecycle.c ../../common/on_close.c ../is_wall.c ../minimap_render.c\
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
