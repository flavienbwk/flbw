CC				=   g++

NAME			=   flbw_libmy
NAME_ST_LIB		=   $(NAME).a
NAME_DYN_LIB	=   $(NAME).so

SRC =				./src/my_strlen.c \
					./src/my_strtolower.c

OBJ				=   $(SRC:%.c=%.o)

RM				=   -rm -f

CFLAGS			=	-Wall -Werror -Wpedantic -Wno-write-strings -fPIC -std=c++11 -I inc/

all:		    	base64_dynamic base64_static

base64_dynamic:  	$(OBJ)
					$(CC) -shared $(OBJ) $(CFLAGS) -o $(NAME_DYN_LIB)
	
base64_static:  	$(OBJ)
					ar rc $(NAME_ST_LIB) $(OBJ)
					ranlib $(NAME_ST_LIB)

re:		    		fclean all

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_ST_LIB)
					$(RM) $(NAME_DYN_LIB)
	
fclean:			    clean
					$(RM) $(NAME_ST_LIB) $(NAME_DYN_LIB)

.PHONY:		    	all base64_dynamic base64_static clean fclean re