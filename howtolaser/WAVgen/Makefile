SRC=main.c waveforms.c gen_programs.c random.c tools.c error.c
OBJ=$(SRC:%.c=%.o)
INC=wavgen.h 

NAME=WAVgen
CC=clang
CFLAGS=-Wall -Werror -Wextra -Wno-unused-function

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) -o $(NAME) -lm $(OBJ)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf rec/*

re: fclean all

.PHONY: all clean fclean re
