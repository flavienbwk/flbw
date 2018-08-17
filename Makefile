CC				=   g++

MAIN_PRGM		=   main.cpp
TEST_PRGM		=	test.cpp
BNCH_PRGM		=   benchmark.cpp

NAME_PRGM		=   flbw
NAME_PRGM_TEST	=   flbw_test

LIB_PROGRAM		=   flbw.a
LIB_CRYPTOPP	=	lib/cryptopp
LIB_BASE64 		=	lib/base64
LIB_MY 			=	lib/libmy

SRC				=   ./flbw.cpp

OBJ				=   $(SRC:%.cpp=%.o)

RM				=   -rm -f

CPPFLAGS 		=  -std=c++14

bindprgm:			make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_PRGM) $(MAIN_PRGM) $(LIB_PROGRAM) $(LIB_CRYPTOPP)/libcryptopp.a $(LIB_BASE64)/flbw_base64.a $(LIB_MY)/flbw_libmy.a -I $(LIB_MY)/inc

test:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_PRGM_TEST) $(TEST_PRGM) $(LIB_PROGRAM) $(LIB_CRYPTOPP)/libcryptopp.a $(LIB_BASE64)/flbw_base64.a $(LIB_MY)/flbw_libmy.a -I $(LIB_MY)/inc

$(LIB_PROGRAM):		$(OBJ)
					ar rc $(LIB_PROGRAM) $(OBJ)
					ranlib $(LIB_PROGRAM)
					chmod +x $(LIB_PROGRAM)
				
make_libs:
					make -C $(LIB_MY)
					make -C $(LIB_CRYPTOPP) all
					make -C $(LIB_BASE64) all

all:				bindprgm

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_PRGM)
					$(RM) $(NAME_PRGM_TEST)
					$(RM) $(LIB_PROGRAM)
					$(RM) main.o
	
fclean:				clean
					$(RM) $(LIB_PROGRAM)
					make -C $(LIB_CRYPTOPP) clean
					make -C $(LIB_BASE64) fclean
					make -C $(LIB_MY) fclean

re:		    		fclean all

.PHONY:		    	$(LIB_CRYPTOPP) all clean fclean re
