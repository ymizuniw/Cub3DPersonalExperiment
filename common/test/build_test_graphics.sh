#!/bin/bash

cc test_graphics_units.c ../ft_put_pixel.c ../clear_img.c ../../minimap/fill_rect.c ../../minimap/draw_line.c \
  -I../includes \
  -I../../minimap/includes \
  -lm