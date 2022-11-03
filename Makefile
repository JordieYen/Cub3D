NAME = cub3D
SOURCES = cube3d.c \
			ft_cube_utils.c \
			ft_shadows.c \
			ft_textures.c \
			ft_textures_utils.c \
			ft_render_utils.c \
			ft_render_utils_2.c \
			render.c \
			cube_doors.c \
			cube_parser.c \
			cube_parser_utils.c \
			cube_move.c \
			frees.c \
			weapon_manipulation.c \
			render_minimap.c \
			frames.c \
			cube_extra.c \
			error.c \
			minecraft.c \

SRC_DIR = src/
OBJECTS = $(addprefix $(SRC_DIR), $(SOURCES:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx

MLX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJECTS) gnl libft
	$(CC) -o $@ $(OBJECTS) -Llibft -lft -Llibmlx $(MLX) -Llibgnl -lgnl

$(SRC_DIR)%.o: %.c
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
	make -C libft fclean
	make -C libgnl fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all libft libgnl clean fclean re