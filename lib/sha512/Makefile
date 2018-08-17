CC				=   g++

NAME			=   flbw_sha512
NAME_ST_LIB		=   $(NAME).a
NAME_DYN_LIB	=   $(NAME).so

SRC				=   ./sha512.cpp

OBJ				=   $(SRC:%.cpp=%.o)

RM				=   -rm -f

CXXFLAGS		=   -Wall -Wextra -Werror -Wpedantic -fPIC -std=c++11

all:		    	sha512_dynamic sha512_static

sha512_dynamic:  	$(OBJ)
		    		$(CC) -shared $(OBJ) $(CXXFLAGS) -o $(NAME_DYN_LIB)
	
sha512_static:   	$(OBJ)
					ar rc $(NAME_ST_LIB) $(OBJ)
					ranlib $(NAME_ST_LIB)

re:		    		fclean all

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_ST_LIB)
					$(RM) $(NAME_DYN_LIB)
	
fclean:		    	clean
		   			$(RM) $(NAME_ST_LIB) $(NAME_DYN_LIB)

.PHONY:		    	all sha512_dynamic sha512_static clean fclean re