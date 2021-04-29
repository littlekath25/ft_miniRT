# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kfu <kfu@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/14 23:09:58 by kfu           #+#    #+#                  #
#    Updated: 2021/04/28 17:32:04 by kfu           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 		libft.a
AR =		ar
H_FILES = 	libft.h
CC = 		gcc
RM =		rm -f
CFLAGS = 	-Wall -Wextra -Werror
O_FILES = 	$(SRC:.c=.o)
SRC = 		ft_strlen.c			ft_strchr.c\
			ft_strdup.c			ft_strjoin.c\
			ft_substr.c			ft_split.c\
			ft_atoi.c			ft_isdigit.c\
			ft_memset.c			ft_atof.c\
			ft_strncmp.c		ft_isequal.c\
			ft_free_split.c		ft_lstadd_back.c\
			ft_lstadd_front.c	ft_lstclear.c\
			ft_lstdelone.c		ft_lstiter.c\
			ft_lstlast.c		ft_lstnew.c\
			ft_lstsize.c		ft_calloc.c\
			ft_strcmp.c			ft_strncmp_rev.c\
			ft_strlcpy.c		ft_memcpy.c

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(AR) rcs $(NAME) $(O_FILES)

%.o: %.c $(H_FILES)
	$(CC) -c $(CFLAGS) -I /includes/ -o $@ $<

clean:
	$(RM) $(O_FILES) $(BO_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all