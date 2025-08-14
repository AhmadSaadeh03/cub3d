CC = cc
CFLAGS = -Wall -Werror -Wextra -g
MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lm -lmlx -lXext -lX11
LIBFT_DIR = ./libft
NAME = cub3d
SRC = srcs/main.c srcs/directions.c srcs/cleanup.c srcs/map.c srcs/ceil.c srcs/floor.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
