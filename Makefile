CC				=   g++

MAIN_PRGM		=   main.cpp
T_IB_PRGM		=	tests/integrity_benchmark.cpp
T_RA_PRGM		=	tests/random_attack.cpp
T_FI_PRGM		=	tests/files_integrity/files_integrity.cpp
BNCH_PRGM		=   benchmark.cpp

NAME_PRGM		=   flbw
NAME_T_IB_PRGM	=   tib
NAME_T_RA_PRGM	=   tra
NAME_T_FI_PRGM	=   tfi

LIB_PROGRAM		=   flbw.a
LIB_SHA1		=	lib/sha1
LIB_SHA256		=	lib/sha256
LIB_SHA512		=	lib/sha512
LIB_BASE64 		=	lib/base64

LIBS			= 	$(LIB_PROGRAM) $(LIB_SHA1)/flbw_sha1.a $(LIB_SHA256)/flbw_sha256.a $(LIB_SHA512)/flbw_sha512.a $(LIB_BASE64)/flbw_base64.a

SRC				=   ./flbw.cpp

OBJ				=   $(SRC:%.cpp=%.o)

RM				=   -rm -f
CP				=	cp -Rf

CPPFLAGS 		=  -std=c++11

all:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_PRGM) $(MAIN_PRGM) $(LIBS)

tib:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_T_IB_PRGM) $(T_IB_PRGM) $(LIBS)

tra:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_T_RA_PRGM) $(T_RA_PRGM) $(LIBS)

tfi:				make_libs $(LIB_PROGRAM)
					base64 /dev/urandom | head -c 1000000 > tests/files_integrity/files/test1.txt
					base64 /dev/urandom | head -c 5000000 > tests/files_integrity/files/test2.txt
					base64 /dev/urandom | head -c 10000000 > tests/files_integrity/files/test3.txt
					base64 /dev/urandom | head -c 25000000 > tests/files_integrity/files/test4.txt
					base64 /dev/urandom | head -c 50000000 > tests/files_integrity/files/test5.txt
					$(CC) $(CPPFLAGS) -o $(NAME_T_FI_PRGM) $(T_FI_PRGM) $(LIBS)

test:				tib tra tfi

$(LIB_PROGRAM):		$(OBJ)
					ar rc $(LIB_PROGRAM) $(OBJ)
					ranlib $(LIB_PROGRAM)
					chmod +x $(LIB_PROGRAM)
				
make_libs:
					make -C $(LIB_SHA1) all
					make -C $(LIB_SHA256) all
					make -C $(LIB_SHA512) all
					make -C $(LIB_BASE64) all

# Make the "flbw" command globally available.
install:			all
					${CP} ${NAME_PRGM} /bin

uninstall:			
					${RM} /bin/${NAME_PRGM}

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_PRGM)
					$(RM) $(NAME_T_IB_PRGM)
					$(RM) $(NAME_T_RA_PRGM)
					$(RM) $(NAME_T_FI_PRGM)
					$(RM) $(LIB_PROGRAM)
					$(RM) main.o
	
fclean:				clean
					$(RM) $(LIB_PROGRAM)
					$(RM) ./tests/files_integrity/files/*
					make -C $(LIB_SHA1) fclean
					make -C $(LIB_SHA256) fclean
					make -C $(LIB_SHA512) fclean
					make -C $(LIB_BASE64) fclean

re:		    		fclean all

.PHONY:		    	$(LIB_CRYPTOPP) all clean fclean re
