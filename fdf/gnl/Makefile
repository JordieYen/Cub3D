NAME = lib_get_next_line.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -c

AR = ar rc

RL = ranlib

SRC = get_next_line.c \
	  get_next_line_utils.c

OBJ = ./*.o

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@$(RL) $(NAME)

$(OBJ): $(SRC) 
	@$(CC) $(CFLAGS) $(SRC)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
