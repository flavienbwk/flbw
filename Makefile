CC				=   g++

MAIN_PRGM		=   main.cpp
TEST_PRGM		=	test.cpp
BNCH_PRGM		=   benchmark.cpp

NAME_PRGM		=   flbw
NAME_PRGM_TEST	=   flbw_test

LIB_PROGRAM		=   flbw.a
LIB_SHA1		=	lib/sha1
LIB_SHA256		=	lib/sha256
LIB_SHA512		=	lib/sha512
LIB_BASE64 		=	lib/base64

SRC				=   ./flbw.cpp

OBJ				=   $(SRC:%.cpp=%.o)

RM				=   -rm -f

CPPFLAGS 		=  -std=c++11

bindprgm:			make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_PRGM) $(MAIN_PRGM) $(LIB_PROGRAM) $(LIB_SHA1)/flbw_sha1.a $(LIB_SHA256)/flbw_sha256.a $(LIB_SHA512)/flbw_sha512.a $(LIB_BASE64)/flbw_base64.a

test:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_PRGM_TEST) $(TEST_PRGM) $(LIB_PROGRAM) $(LIB_SHA1)/flbw_sha1.a $(LIB_SHA256)/flbw_sha256.a $(LIB_SHA512)/flbw_sha512.a $(LIB_BASE64)/flbw_base64.a

$(LIB_PROGRAM):		$(OBJ)
					ar rc $(LIB_PROGRAM) $(OBJ)
					ranlib $(LIB_PROGRAM)
					chmod +x $(LIB_PROGRAM)
				
make_libs:
					make -C $(LIB_SHA1) all
					make -C $(LIB_SHA256) all
					make -C $(LIB_SHA512) all
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
					make -C $(LIB_SHA1) fclean
					make -C $(LIB_SHA256) fclean
					make -C $(LIB_SHA512) fclean
					make -C $(LIB_BASE64) fclean

re:		    		fclean all

.PHONY:		    	$(LIB_CRYPTOPP) all clean fclean re
