CC				=   g++

NAME			=   flbw
NAME_ST_LIB		=   $(NAME).a
NAME_DYN_LIB	=   $(NAME).so

LIB_CRYPTOPP 	=	./lib/cryptopp
LIB_BASE64		=	./lib/base64
LIB_MY 			= 	./lib/libmy

SRC =				./flbw.cpp

OBJ				=   $(SRC:%.cpp=%.o)

LN				= 	ln -sf
RM				=   -rm -f

CXXFLAGS		=	-Wall -Wpedantic -fPIC -std=c++11

all:				make_libs base64_dynamic base64_static

base64_dynamic: 	$(OBJ)
					${LN} $(LIB_CRYPTOPP)/libcryptopp.so.7 ./
					${LN} $(LIB_BASE64)/flbw_base64.so ./
					${LN} $(LIB_MY)/flbw_libmy.so ./
					$(CC) -shared $(OBJ) $(CXXFLAGS) -o $(NAME_DYN_LIB) libcryptopp.so.7 flbw_base64.so flbw_libmy.so
	
base64_static:  	$(OBJ)
					ar rc $(NAME_ST_LIB) $(OBJ)
					ranlib $(NAME_ST_LIB)

make_libs:
					make -C $(LIB_MY)
					make -C $(LIB_CRYPTOPP) all
					make -C $(LIB_BASE64) all

re:		    		fclean all

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_ST_LIB)
					$(RM) $(NAME_DYN_LIB)
	
fclean:				clean
					$(RM) $(NAME_ST_LIB) $(NAME_DYN_LIB)
					make -C $(LIB_CRYPTOPP) clean
					make -C $(LIB_BASE64) fclean
					make -C $(LIB_MY) fclean
					${RM} ./*.so*

.PHONY:		    	all base64_dynamic base64_static clean fclean re