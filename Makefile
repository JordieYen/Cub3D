NAME = cube3d
SOURCES = cube3d.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx

all: $(NAME)

$(NAME): $(OBJECTS) libft gnl
	$(CC) -o $@ $(OBJECTS) -Llibft -lft -Lmlx -lmlx -Llibgnl -lgnl

%.o: %.c
	$(CC) -c $(CFLAGS) $?

gnl:
	make -C libgnl

libft:
	make -C libft

clean:
	$(RM) $(OBJECTS)
	make -C libft clean
	make -C libgnl clean

fclean: clean
	$(RM) $(NAME) libft/libft.a
	$(RM) $(NAME) libgnl/libgnl.a

re: fclean all

.PHONY: all libft clean fclean re