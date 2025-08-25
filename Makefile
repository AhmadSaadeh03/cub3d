CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -L. -lm -lmlx -lXext -lX11
LIBFT_DIR = ./libft
NAME = cub3d

#utils.c additional_files.c main.c textures_config.c ray_casting.c draw.c movement.c initialization.c

SRC = 

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
