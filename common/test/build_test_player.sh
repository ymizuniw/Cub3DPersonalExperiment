#!/bin/bash

cc test_player_units.c ../player_set_dir.c ../rotate_player.c \
  -I../includes \
  -I../../vector/includes \
  ../../vector/vector.a \
  -lm