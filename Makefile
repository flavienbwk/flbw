CC				=   g++

MAIN_PRGM		=   main.cpp
T_IB_PRGM		=	tests/integrity_benchmark.cpp
T_RA_PRGM		=	tests/random_attack.cpp
BNCH_PRGM		=   benchmark.cpp

NAME_PRGM		=   flbw
NAME_T_IB_PRGM	=   tib
NAME_T_RA_PRGM	=   tra

LIB_PROGRAM		=   flbw.a
LIB_SHA1		=	lib/sha1
LIB_SHA256		=	lib/sha256
LIB_SHA512		=	lib/sha512
LIB_BASE64 		=	lib/base64

LIBS			= 	$(LIB_PROGRAM) $(LIB_SHA1)/flbw_sha1.a $(LIB_SHA256)/flbw_sha256.a $(LIB_SHA512)/flbw_sha512.a $(LIB_BASE64)/flbw_base64.a

SRC				=   ./flbw.cpp

OBJ				=   $(SRC:%.cpp=%.o)

RM				=   -rm -f

CPPFLAGS 		=  -std=c++11

all:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_PRGM) $(MAIN_PRGM) $(LIBS)

tib:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_T_IB_PRGM) $(T_IB_PRGM) $(LIBS)

tra:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_T_RA_PRGM) $(T_RA_PRGM) $(LIBS)

test:				tib tra

$(LIB_PROGRAM):		$(OBJ)
					ar rc $(LIB_PROGRAM) $(OBJ)
					ranlib $(LIB_PROGRAM)
					chmod +x $(LIB_PROGRAM)
				
make_libs:
					make -C $(LIB_SHA1) all
					make -C $(LIB_SHA256) all
					make -C $(LIB_SHA512) all
					make -C $(LIB_BASE64) all

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_PRGM)
					$(RM) $(NAME_T_IB_PRGM)
					$(RM) $(NAME_T_RA_PRGM)
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
