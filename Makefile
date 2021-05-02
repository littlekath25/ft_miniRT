# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kfu <kfu@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/14 23:09:58 by kfu           #+#    #+#                  #
#    Updated: 2021/05/02 09:52:03 by katherine     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= 	miniRT
CC		= 	gcc
RM		=	rm -f
FLAGS	= 	-Wall -Wextra -Werror -I includes/
MACRO	=	-DLINUX=1
LIBS	=	-Llibft -lft
MLIB	=	 -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o
LLIB	=	-Lmlx_linux -lmlx -lXext -lX11 -lm -lz -o
UNAME_S := 	$(shell uname -s)

H_FILES	= 	get_next_line.h		info.h\
			libft.h				mini_rt.h\
			mlx_mac.h			mlx.h
H_PATH	=	includes/

M_SRC	= 	miniRT.c
M_PATH	=	src/
M_OBJ	=	$(M_SRC:%.c=$(M_PATH)%.o)

P_SRC	=	parsing.c		parse_info.c\
			parse_object.c	fill_struct.c
P_PATH	=	src/parsing/
P_OBJ	=	$(P_SRC:%.c=$(P_PATH)%.o)

I_SRC	=	ray.c			intersect.c\
			shade.c			sphere.c\
			plane.c			triangle.c\
			square.c			cylinder.c
I_PATH	=	src/intersect/
I_OBJ	=	$(I_SRC:%.c=$(I_PATH)%.o)

U_SRC	=	error.c			miscellaneous.c\
			vector_utils.c	vector_utils_2.c\
			color.c			bmp.c\
			init.c			debugray.c\
			get_next_line.c
U_PATH	=	utils/
U_OBJ	=	$(U_SRC:%.c=$(U_PATH)%.o)

OBJ_FILES = $(L_OBJ) $(P_OBJ) $(M_OBJ) $(U_OBJ) $(I_OBJ)

all: $(NAME)

ifeq ($(UNAME_S),Linux)
FLAGS += $(MACRO)
LIBS += $(LLIB)
else
LIBS += $(MLIB)
endif

$(NAME): $(OBJ_FILES)
	cd libft && make
	cp mlx/libmlx.dylib .
	$(CC) $(OBJ_FILES) $(LIBS) $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME) libmlx.dylib && cd libft && make fclean

re: fclean all
