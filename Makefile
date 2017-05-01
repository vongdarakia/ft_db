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

NAME		=	a.out

IDIR		=	includes
CC			=	gcc
# CFLAGS		=	-Wall -Wextra
SRCS		= 	main.c \
				database.c \
				table.c \
				write_data.c \
				read_table.c \
				ft_strsplit.c \
				free.c \
				print_table.c \
				entry_queries.c \
				db_queries.c \
				error_mngr.c \
				parse_input.c \
				display.c

ODIR		=	build
OBJS		=	$(addprefix build/, $(SRCS:.c=.o)) 

.PHONY: all clean fclean re

all: $(NAME)

build:
	@mkdir build/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

build/%.o: src/%.c | build
	$(CC) -I includes/ $(CFLAGS) -c $< -o $@

$(LIB):
	make re -C lib/libft/

clean:
	rm -f $(ODIR)/*.o 
	rm -rf build

fclean: clean
	rm -f $(NAME)
	# make fclean -C lib/libft/

re: fclean all
