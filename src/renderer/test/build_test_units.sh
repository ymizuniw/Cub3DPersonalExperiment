#!/bin/bash

cc test_raycasting_units.c \
  ../../common/ft_put_pixel.c \
  -I../../common/includes \
  -I../../parse_map/includes \
  -I../../vector/includes \
  -I../../minimap/includes \
  ../../vector/vector.a \
  -lm
