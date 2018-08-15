CC	=	g++

NAME	=	libmy.a

COMPILE_PATH = ./bin/

SRC =	./src/my_strlen.c \
		./src/my_strtolower.c

OBJ	=	$(SRC:%.c=%.o)

RM	=	-rm -f

CFLAGS	=	-Wall -Werror -Wpedantic -Wno-write-strings

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)


all:		$(NAME)

clean:	
		$(RM) $(OBJ)
		$(RM) -rf ./src/*.o

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(OBJ)


re:		fclean all

.PHONY:		all clean fclean re