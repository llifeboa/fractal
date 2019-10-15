NAME = fractol

SRCLIST = main.c help.c
SRC = $(addprefix ./src/, $(SRCLIST))

OBJ = $(SRC:.c=.o)

FLAGS = -g
MLX = -I ./minilibx -L ./minilibx -l mlx -framework OpenGL -framework AppKit -framework OpenCL

HEADERS = includes/fractol.h libft/libft.h minilibx/mlx.h

INCLUDES = -I includes/ -I libft/ -I minilibx/

LIBFT = ./libft/libft.a

all:
	make -C libft
	make $(NAME)
	
$(NAME): $(OBJ) $(HEADERS) $(LIBFT)
	gcc -o $(NAME) $(OBJ) $(FLAGS) $(MLX) $(LIBFT) $(INCLUDES)

%.o: %.c $(HEADERS) 
	gcc -c $< $(FLAGS) -o $@ $(INCLUDES)

clean:
	rm -rf src/*.o
	make clean -C libft
fclean: clean
	rm -rf fdf
	make fclean -C libft

dev:
	while true; do clear; make; sleep 1; done