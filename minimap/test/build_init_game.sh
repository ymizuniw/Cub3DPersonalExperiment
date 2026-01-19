#!/bin/bash

cc test_init_game.c ../../common/game_mlx.c ../../common/game_player_init.c ../../common/game_minimap_init.c ../../common/game_lifecycle.c ../../common/on_close.c ../../common/player_set_dir.c \
  -I../includes \
  -I../../common/includes \
  -I../../parse_map/includes \
  -I../../minilibx_opengl_20191021 \
  -L../../parse_map -lparse_map \
  -L../../minilibx_opengl_20191021 -lmlx \
  -framework OpenGL -framework AppKit
