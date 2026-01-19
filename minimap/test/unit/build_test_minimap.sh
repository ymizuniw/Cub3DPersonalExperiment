#!/bin/bash

cc test_minimap_units.c ../../is_wall.c ../../fill_rect.c \
  ../../../common/clear_img.c ../../../common/ft_put_pixel.c \
  -I../../includes \
  -I../../../common/includes \
  -I../../../parse_map/includes \
  -I../../../vector/includes \
  -lm