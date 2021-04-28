# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kfu <kfu@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/14 23:09:58 by kfu           #+#    #+#                  #
#    Updated: 2021/04/28 17:22:19 by kfu           ########   odam.nl          #
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

P_SRC	=	parsing.c\
			parse_info.c\
			parse_object.c\
			fill_struct.c
P_PATH	=	src/parsing/
P_OBJ	=	$(P_SRC:%.c=$(P_PATH)%.o)

I_SRC	=	ft_ray.c\
			ft_intersect.c\
			ft_shade.c\
			ft_sphere.c\
			ft_plane.c\
			ft_triangle.c\
			ft_square.c\
			ft_cylinder.c
I_PATH	=	src/intersect/
I_OBJ	=	$(I_SRC:%.c=$(I_PATH)%.o)


L_SRC	=	ft_strlen.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_strjoin.c\
			ft_substr.c\
			ft_split.c\
			ft_atoi.c\
			ft_isdigit.c\
			ft_memset.c\
			ft_atof.c\
			ft_strncmp.c\
			ft_isequal.c\
			ft_free_split.c\
			ft_lstadd_back.c\
			ft_lstadd_front.c\
			ft_lstclear.c\
			ft_lstdelone.c\
			ft_lstiter.c\
			ft_lstlast.c\
			ft_lstnew.c\
			ft_lstsize.c\
			ft_calloc.c\
			ft_strcmp.c\
			ft_strncmp_rev.c\
			ft_strlcpy.c\
			ft_memcpy.c
L_PATH	=	libft/
L_OBJ	=	$(L_SRC:%.c=$(L_PATH)%.o)

U_SRC	=	ft_error.c\
			ft_miscellaneous.c\
			ft_vector_math.c\
			ft_vector_math_2.c\
			ft_color.c\
			ft_bmp.c\
			ft_init.c\
			debugray.c\
			get_next_line.c
U_PATH	=	utils/
U_OBJ	=	$(U_SRC:%.c=$(U_PATH)%.o)

OBJ_FILES = $(L_OBJ) $(P_OBJ) $(M_OBJ) $(U_OBJ) $(I_OBJ)

all: $(NAME)

ifeq ($(UNAME_S),Linux)
	$(NAME): $(OBJ_FILES)
		$(CC) $(OBJ_FILES)  -Lmlx_linux -lmlx -lXext -lX11 -lm -lz -o $(NAME)
else
	$(NAME): $(OBJ_FILES)
		$(CC) $(OBJ_FILES) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) && cp mlx/libmlx.dylib .
endif

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $< -I includes/

clean:
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all
