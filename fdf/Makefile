NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

LIBFT = -Llibft -lft

GNL = -Lgnl -l_get_next_line

MLX = -lmlx -framework OpenGL -framework AppKit

INCLUDES = -Iincludes -Ilibft -Ignl -Imlx

MAIN = fdf.c 

SRC =	cartesianplane.c \
		frees.c \
		inits.c \
		pixeledit.c \
		chart_utils.c 

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): #${OBJ}
	make -C libft
	make -C gnl
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ ${MAIN} ${SRC} $(LIBFT) $(MLX) $(GNL)
	# rm -rf *.dSYM

clean:
	@$(RM) $(OBJ)
	make clean -C libft
	make clean -C gnl

fclean: clean
	@$(RM) $(NAME)
	make fclean -C libft
	make fclean -C gnl

test: re
	./$(NAME) testfiles/42.fdf

dc: re
	./$(NAME) testfiles/53.fdf

re: fclean all

.PHONY: clean fclean