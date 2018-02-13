SRC=main.c gen_audio.c random.c tools.c error.c
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
