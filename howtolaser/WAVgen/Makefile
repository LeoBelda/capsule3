SRCFILES=main.c \
		 machine_program.c gen_programs.c random.c \
		 shaderz_program.c test_funcs.c \
		 ps3_program.c events.c \
		 waveforms.c tools.c error.c \
		 tinyosc/oscmain.c tinyosc/tinyosc.c
SRCDIR=src/
SRC=$(addprefix $(SRCDIR), $(SRCFILES))

OBJ=$(SRC:%.c=%.o)

INCFILES=wavgen.h tinyosc.h
INCDIR=include/
INC=$(addprefix $(INCDIR), $(INCFILES))

LIBDIR=libs/
SDLDIR=$(addprefix $(LIBDIR), SDL2/lib/)
SDLINCDIR=$(addprefix $(LIBDIR), SDL2/include/)
LIBSDL=libSDL2.a
SDLLK=SDL2

RPATHSDL=\$$ORIGIN/libs/SDL2/lib/

NAME=WAVgen
CC=clang
CFLAGS=-Wall -Werror -Wextra -Wno-unused-function \
	   -Wno-unused-parameter -Wno-unused-variable -Wno-format\
	   -Wno-sign-compare

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) -o $(NAME) -I$(INCDIR) -I$(SDLINCDIR) -L$(SDLDIR) -l$(SDLLK) -lasound -lm $(OBJ) -Wl,-rpath,$(RPATHSDL)


%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(SDLINCDIR) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf bank/*

re: fclean all

.PHONY: all clean fclean re
