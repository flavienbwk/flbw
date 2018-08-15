CC		=	g++

NAME	=	base64.a

COMPILE_PATH = ./bin/

SRC 	=	./base64.cpp

OBJ		=	$(SRC:%.cpp=%.o)

RM		=	-rm -f

CFLAGS	=	-Wall -Werror -Wpedantic -Wno-write-strings -std=c++11

$(NAME):	$(OBJ)
			ar rc $(NAME) $(OBJ)
			ranlib $(NAME)

all:		$(NAME)

clean:	
			$(RM) $(NAME)

fclean:		clean
			$(RM) $(OBJ)

re:			fclean all

.PHONY:		all clean fclean re