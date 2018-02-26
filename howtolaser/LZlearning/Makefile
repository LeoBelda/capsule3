NAME=		slazzers

SRC_PATH=	src

OBJ_PATH=	obj

CPPFLAGS=	-Iinclude

SRC_NAME=	main.c\
			init_nn.c\
			init_samples.c\
			shoot_lasers.c\
			gphoto2_command.c\
			get_splatter_target.c\
			reload_cannons.c\
			adjust_aim.c\

SRC=		$(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ=		$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

OBJ_NAME=	$(SRC_NAME:.c=.o)

##
##		COMPILER FLAGS
##

CFLAGS=		-Werror -Wextra -Wall

CC=			gcc

LIBS=		-Llib -lft -lm

LDLIBS=		$(LDFLAGS) $(LIBS)

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDLIBS)
				@echo "compiled $@."

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
				@mkdir $(OBJ_PATH) 2> /dev/null || true
				$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

##
##		Use fclean to clean this program.
##

clean:
				@rm -Rf $(OBJ_PATH)
				@echo "clean"

fclean:			clean
				@rm -f $(NAME)
				@echo "fclean"

re:				fclean all

.PHONY:			all clean fclean re
