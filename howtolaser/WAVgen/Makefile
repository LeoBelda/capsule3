# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbelda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 08:45:00 by lbelda            #+#    #+#              #
#    Updated: 2018/02/13 14:13:51 by lbelda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC=main.c file.c error.c
OBJ=$(SRC:%.c=%.o)
INC=wavgen.h 

NAME=WAVgen
CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) -o $(NAME) $(OBJ)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf rec/*

re: fclean all

.PHONY: all clean fclean re
