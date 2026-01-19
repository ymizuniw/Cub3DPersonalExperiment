#!/bin/bash

echo "Building Cub3D..."

# Build vector library first
cd vector && bash build.sh && cd ..

# Collect all source files  
SOURCES="cub3d.c"

# Common sources
SOURCES="$SOURCES common/game_mlx.c"
SOURCES="$SOURCES common/game_lifecycle.c" 
SOURCES="$SOURCES common/game_player_init.c"
SOURCES="$SOURCES common/game_minimap_init.c"
SOURCES="$SOURCES common/player_set_dir.c"
SOURCES="$SOURCES common/player_plane.c"
SOURCES="$SOURCES common/rotate_player.c"
SOURCES="$SOURCES common/ft_put_pixel.c"
SOURCES="$SOURCES common/clear_img.c"
SOURCES="$SOURCES common/on_close.c"

# Input handling
SOURCES="$SOURCES minimap/on_keypress.c"
SOURCES="$SOURCES minimap/on_wsad.c"
SOURCES="$SOURCES minimap/on_right_left.c"

# Minimap utilities
SOURCES="$SOURCES minimap/is_wall.c"

# Raycasting
SOURCES="$SOURCES raycasting/raycasting.c"

# Parse map sources
SOURCES="$SOURCES parse_map/parse_data.c"
SOURCES="$SOURCES parse_map/read_data.c"
SOURCES="$SOURCES parse_map/process_data.c"
SOURCES="$SOURCES parse_map/judge_data.c"
SOURCES="$SOURCES parse_map/map_builder.c"
SOURCES="$SOURCES parse_map/map_info_fn.c"
SOURCES="$SOURCES parse_map/map_normalize_rectangle.c"
SOURCES="$SOURCES parse_map/map_scan_set_start.c"
SOURCES="$SOURCES parse_map/map_validate_closed.c"
SOURCES="$SOURCES parse_map/flag_status_ok.c"
SOURCES="$SOURCES parse_map/ft_putstr_fd.c"
SOURCES="$SOURCES parse_map/get_next_line.c"

# Include directories
INCLUDES="-I common/includes"
INCLUDES="$INCLUDES -I minimap/includes"
INCLUDES="$INCLUDES -I parse_map/includes"
INCLUDES="$INCLUDES -I raycasting/includes"
INCLUDES="$INCLUDES -I vector/includes"
INCLUDES="$INCLUDES -I minilibx_opengl_20191021"

# Libraries
LIBS="vector/vector.a"
LIBS="$LIBS -Lminilibx_opengl_20191021 -lmlx"
LIBS="$LIBS -framework OpenGL -framework AppKit"
LIBS="$LIBS -lm"

# Compile
echo "Compiling with sources: $SOURCES"
gcc -Wall -Wextra -Werror $INCLUDES $SOURCES $LIBS -o cub3d

if [ $? -eq 0 ]; then
    echo "✅ Build successful! Run './cub3d map_file.cub' to start"
else
    echo "❌ Build failed"
    exit 1
fi