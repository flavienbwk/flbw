CC				=   g++

NAME			=   flbw_base64
NAME_ST_LIB		=   $(NAME).a
NAME_DYN_LIB	=   $(NAME).so

SRC				=   ./base64.cpp

OBJ				=   $(SRC:%.cpp=%.o)

RM				=   -rm -f

CXXFLAGS		=   -Wall -Wextra -Werror -Wpedantic -fPIC

all:		    	base64_dynamic base64_static

base64_dynamic:  	$(OBJ)
		    		$(CC) -shared $(OBJ) $(CXXFLAGS) -o $(NAME_DYN_LIB)
	
base64_static:   	$(OBJ)
					ar rc $(NAME_ST_LIB) $(OBJ)
					ranlib $(NAME_ST_LIB)

re:		    		fclean all

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_ST_LIB)
					$(RM) $(NAME_DYN_LIB)
	
fclean:		    	clean
		   			$(RM) $(NAME_ST_LIB) $(NAME_DYN_LIB)

.PHONY:		    	all base64_dynamic base64_static clean fclean re