# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kfu <kfu@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/14 23:09:58 by kfu           #+#    #+#                  #
#    Updated: 2021/04/28 17:37:30 by kfu           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= 	miniRT
CC		= 	gcc
RM		=	rm -f
CFLAGS	= 	-Wall -Wextra -Werror
UNAME_S := 	$(shell uname -s)

M_SRC	= 	miniRT.c
M_PATH	=	src/
M_OBJ	=	$(M_SRC:%.c=$(M_PATH)%.o)

P_SRC	=	ft_parsing.c		ft_parse_info.c\
			ft_parse_object.c	ft_fill_struct.c
P_PATH	=	src/parsing/
P_OBJ	=	$(P_SRC:%.c=$(P_PATH)%.o)

I_SRC	=	ft_ray.c			ft_intersect.c\
			ft_shade.c			ft_sphere.c\
			ft_plane.c			ft_triangle.c\
			ft_square.c			ft_cylinder.c
I_PATH	=	src/intersect/
I_OBJ	=	$(I_SRC:%.c=$(I_PATH)%.o)

U_SRC	=	ft_error.c			ft_miscellaneous.c\
			ft_vector_math.c	ft_vector_math_2.c\
			ft_color.c			ft_bmp.c\
			ft_init.c			debugray.c\
			get_next_line.c
U_PATH	=	utils/
U_OBJ	=	$(U_SRC:%.c=$(U_PATH)%.o)

OBJ_FILES = $(L_OBJ) $(P_OBJ) $(M_OBJ) $(U_OBJ) $(I_OBJ)

all: $(NAME)

ifeq ($(UNAME_S),Linux)
$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES)  -Lmlx_linux -lmlx -Llibft -lft -lXext -lX11 -lm -lz -o $(NAME)
else
$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME) && cp mlx/libmlx.dylib .
endif

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $< -I includes/

clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME) libmlx.dylib

re: fclean all
