# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cub3d <cub3d@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/20 00:00:00 by cub3d             #+#    #+#              #
#    Updated: 2026/01/20 00:00:00 by cub3d            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = cub3d

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
VECTOR_DIR = vector
MLX_DIR = minilibx_opengl_20191021

# Include directories
INCLUDES = -I$(INC_DIR)/core -I$(INC_DIR)/input -I$(INC_DIR)/map_parser -I$(VECTOR_DIR) -I$(MLX_DIR)

# Source files
CORE_SRCS = $(SRC_DIR)/core/cub3d.c \
			$(SRC_DIR)/core/game_lifecycle.c \
			$(SRC_DIR)/core/game_mlx.c \
			$(SRC_DIR)/core/on_close.c

GRAPHICS_SRCS = $(SRC_DIR)/graphics/ft_put_pixel.c \
				$(SRC_DIR)/graphics/clear_img.c

PLAYER_SRCS = $(SRC_DIR)/player/game_player_init.c \
			  $(SRC_DIR)/player/player_plane.c \
			  $(SRC_DIR)/player/player_set_dir.c \
			  $(SRC_DIR)/player/rotate_player.c

INPUT_SRCS = $(SRC_DIR)/input/on_keypress.c \
			 $(SRC_DIR)/input/on_wsad.c \
			 $(SRC_DIR)/input/on_right_left.c \
			 $(SRC_DIR)/input/minimap_render.c \
			 $(SRC_DIR)/input/draw_player_dir.c \
			 $(SRC_DIR)/input/draw_line.c \
			 $(SRC_DIR)/input/fill_rect.c

GAME_LOGIC_SRCS = $(SRC_DIR)/game_logic/is_wall.c \
				  $(SRC_DIR)/game_logic/game_minimap_init.c

RENDERER_SRCS = $(SRC_DIR)/renderer/raycasting.c

MAP_PARSER_SRCS = $(SRC_DIR)/map_parser/parse_data.c \
				  $(SRC_DIR)/map_parser/read_data.c \
				  $(SRC_DIR)/map_parser/process_data.c \
				  $(SRC_DIR)/map_parser/judge_data.c \
				  $(SRC_DIR)/map_parser/map_builder.c \
				  $(SRC_DIR)/map_parser/map_info_fn.c \
				  $(SRC_DIR)/map_parser/map_normalize_rectangle.c \
				  $(SRC_DIR)/map_parser/map_scan_set_start.c \
				  $(SRC_DIR)/map_parser/map_validate_closed.c \
				  $(SRC_DIR)/map_parser/flag_status_ok.c \
				  $(SRC_DIR)/map_parser/ft_putstr_fd.c \
				  $(SRC_DIR)/map_parser/get_next_line.c

# Vector library source files
VECTOR_SRCS = $(VECTOR_DIR)/add_v2.c \
			  $(VECTOR_DIR)/init_v2.c \
			  $(VECTOR_DIR)/normalize_v2.c \
			  $(VECTOR_DIR)/rotate_v2.c \
			  $(VECTOR_DIR)/subtract_v2.c

# All source files
SRCS = $(CORE_SRCS) $(GRAPHICS_SRCS) $(PLAYER_SRCS) $(INPUT_SRCS) $(GAME_LOGIC_SRCS) $(RENDERER_SRCS) $(MAP_PARSER_SRCS)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
VECTOR_OBJS = $(VECTOR_SRCS:$(VECTOR_DIR)/%.c=$(OBJ_DIR)/vector/%.o)

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

# Main rule
all: $(NAME)

# Build the main program
$(NAME): $(OBJS) $(VECTOR_OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(VECTOR_OBJS) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)✅ Build successful! Run './$(NAME) map_file.cub' to start$(NC)"

# Compile vector object files
$(OBJ_DIR)/vector/%.o: $(VECTOR_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -I$(VECTOR_DIR) -c $< -o $@

# Create object directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/core
	@mkdir -p $(OBJ_DIR)/graphics
	@mkdir -p $(OBJ_DIR)/player
	@mkdir -p $(OBJ_DIR)/input
	@mkdir -p $(OBJ_DIR)/game_logic
	@mkdir -p $(OBJ_DIR)/renderer
	@mkdir -p $(OBJ_DIR)/map_parser
	@mkdir -p $(OBJ_DIR)/vector

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@$(RM) -r $(OBJ_DIR)

# Clean everything
fclean: clean
	@echo "$(YELLOW)Cleaning executable...$(NC)"
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Development targets
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: $(NAME)

# Test build target (preserves test building functionality)
test: CFLAGS += -DTEST_MODE
test: $(NAME)

# Print information about the build
info:
	@echo "$(GREEN)Cub3D Build Information$(NC)"
	@echo "Program: $(NAME)"
	@echo "Compiler: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Sources: $(words $(SRCS)) files"
	@echo "Vector sources: $(words $(VECTOR_SRCS)) files"
	@echo "Includes: $(INCLUDES)"

# Install dependencies (for development)
deps:
	@echo "$(YELLOW)Installing dependencies...$(NC)"
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(RED)Error: MiniLibX directory not found at $(MLX_DIR)$(NC)"; \
		exit 1; \
	fi

# Help target
help:
	@echo "$(GREEN)Cub3D Makefile Help$(NC)"
	@echo "Available targets:"
	@echo "  all     - Build the program (default)"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove object files and executable"
	@echo "  re      - Rebuild everything"
	@echo "  debug   - Build with debug flags and AddressSanitizer"
	@echo "  test    - Build for testing"
	@echo "  info    - Show build information"
	@echo "  deps    - Check dependencies"
	@echo "  help    - Show this help"

.PHONY: all clean fclean re debug test info deps help