NAME = fractol

SRCLIST = main.c help.c reader.c settings.c
SRC = $(addprefix ./src/, $(SRCLIST))

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g
MLX = -I ./minilibx -L ./minilibx -l mlx -framework OpenGL -framework AppKit -framework OpenCL

HEADERS = includes/fractol.h libft/libft.h

INCLUDES = -I includes/ -I libft/ -I minilibx/

LIBFT = ./libft/libft.a

all:
	make -C libft
	make $(NAME)
	
$(NAME): $(OBJ) $(HEADERS) $(LIBFT)
	gcc -o $(NAME) $(OBJ) $(FLAGS) $(MLX) $(INCLUDES) $(LIBFT)

%.o: %.c $(HEADERS) 
	gcc -c $< $(FLAGS) -o $@ $(INCLUDES)

clean:
	rm -rf src/*.o
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

dev:
	while true; do clear; make; sleep 1; done