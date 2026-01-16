#!/bin/bash

cc test_init_game.c \
  -I../ \
  -I../../parse_map/includes \
  -I../../minilibx_opengl_20191021 \
  -L../../parse_map -lparse_map \
  -L../../minilibx_opengl_20191021 -lmlx \
  -framework OpenGL -framework AppKit
