# **************************************************************************** #
#                                                                              #
#                                                        :::      ::::::::     #
#    Makefile                                           :+:      :+:    :+:    #
#                                                    +:+ +:+         +:+       #
#   By: avongdar <avongdar@student.42.us.org>      +#+  +:+       +#+          #
#                                                +#+#+#+#+#+   +#+             #
#   Created: 2017/04/27 16:49:09 by avongdar          #+#    #+#               #
#   Updated: 2017/04/27 16:49:09 by avongdar         ###   ########.fr         #
#                                                                              #
# **************************************************************************** #

LIB			=	lib/libft/libft.a
NAME		=	a.out

IDIR		=	includes
CC			=	gcc
LFLAGS		=	-I lib/libft/includes -L lib/libft/ -lft
SRCS		= 	main.c \
				database.c \
				table.c \
				write_data.c \
				read_table.c

ODIR		=	build
OBJS		=	$(addprefix build/, $(SRCS:.c=.o)) 

.PHONY: all clean fclean re

all: $(NAME)

build:
	@mkdir build/

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

build/%.o: src/%.c | build
	$(CC) -I includes/ -I lib/libft/includes $(CFLAGS) -c $< -o $@

$(LIB):
	make re -C lib/libft/

clean:
	rm -f $(ODIR)/*.o 
	rm -rf build

fclean: clean
	rm -f $(NAME)
	make fclean -C lib/libft/

re: fclean all
