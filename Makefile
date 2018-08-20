CC				=   g++

MAIN_PRGM		=   main.cpp
T_IB_PRGM		=	tests/integrity_benchmark.cpp
T_IBP_PRGM		=	tests/integrity_benchmark_bp.cpp
T_RA_PRGM		=	tests/random_attack.cpp
T_FI_PRGM		=	tests/files_integrity/files_integrity.cpp

NAME_PRGM		=   flbw

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

test:
					make -C tests all

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
					make -C tests clean
					$(RM) $(LIB_PROGRAM)
					$(RM) main.o
	
fclean:				clean
					$(RM) $(LIB_PROGRAM)
					make -C tests fclean
					make -C $(LIB_SHA1) fclean
					make -C $(LIB_SHA256) fclean
					make -C $(LIB_SHA512) fclean
					make -C $(LIB_BASE64) fclean

re:		    		fclean all

.PHONY:		    	all clean fclean re
