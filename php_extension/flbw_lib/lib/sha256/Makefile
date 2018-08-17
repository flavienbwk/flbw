CC				=   g++

NAME			=   flbw_sha256
NAME_ST_LIB		=   $(NAME).a
NAME_DYN_LIB	=   $(NAME).so

SRC				=   ./sha256.cpp

OBJ				=   $(SRC:%.cpp=%.o)

RM				=   -rm -f

CXXFLAGS		=   -Wall -Wextra -Werror -Wpedantic -fPIC

all:		    	sha256_dynamic sha256_static

sha256_dynamic:  	$(OBJ)
		    		$(CC) -shared $(OBJ) $(CXXFLAGS) -o $(NAME_DYN_LIB)
	
sha256_static:   	$(OBJ)
					ar rc $(NAME_ST_LIB) $(OBJ)
					ranlib $(NAME_ST_LIB)

re:		    		fclean all

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_ST_LIB)
					$(RM) $(NAME_DYN_LIB)
	
fclean:		    	clean
		   			$(RM) $(NAME_ST_LIB) $(NAME_DYN_LIB)

.PHONY:		    	all sha256_dynamic sha256_static clean fclean re