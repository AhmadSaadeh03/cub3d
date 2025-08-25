CC = cc
CFLAGS = -Wall -Werror -Wextra -g
MLX_FLAGS = -L. -lm -lmlx -lXext -lX11
LIBFT_DIR = ./libft
NAME = cub3d
SRC = srcs/main.c srcs/directions.c srcs/cleanup.c srcs/map.c srcs/ceil.c srcs/floor.c srcs/initialize.c srcs/rgb.c srcs/flood_fill.c srcs/ceil_helper.c srcs/floor_helper.c \
		srcs/map_helper_one.c srcs/check_walls.c srcs/check_walls_two.c srcs/init_map.c srcs/ceil_utils.c srcs/cleanup_two.c\
		srcs/map_utils.c srcs/set_dir_path.c srcs/read_file.c srcs/validate_res.c srcs/direction_utils.c
#utils.c additional_files.c main.c textures_config.c ray_casting.c draw.c movement.c initialization.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

%.o:%.c ./cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
