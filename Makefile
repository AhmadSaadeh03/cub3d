CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -L. -lm -lmlx -lXext -lX11
OBJ_DIR = OBJ
LIBFT_DIR = ./libft
NAME = cub3d
SRC = srcs/parsing.c srcs/directions.c srcs/cleanup.c srcs/map.c srcs/ceil.c srcs/floor.c srcs/initialize.c srcs/rgb.c srcs/flood_fill.c srcs/ceil_helper.c srcs/floor_helper.c \
		srcs/map_helper_one.c srcs/check_walls.c srcs/check_walls_two.c srcs/init_map.c srcs/ceil_utils.c srcs/cleanup_two.c\
		srcs/map_utils.c srcs/set_dir_path.c srcs/read_file.c srcs/validate_res.c srcs/direction_utils.c\
		srcs/utils.c srcs/textures_config.c srcs/ray_casting.c srcs/draw.c srcs/movement.c srcs/initialization.c srcs/main.c srcs/mlx_manage.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

$(OBJ_DIR)/%.o:%.c ./cub3d.h $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
