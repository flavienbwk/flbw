CC				=   g++

T_IB_PRGM		=	integrity_benchmark.cpp
T_IBP_PRGM		=	integrity_benchmark_bp.cpp
T_RA_PRGM		=	random_attack.cpp
T_FI_PRGM		=	files_integrity/files_integrity.cpp

NAME_T_IB_PRGM	=   tib
NAME_T_IBP_PRGM	=   tibp
NAME_T_RA_PRGM	=   tra
NAME_T_FI_PRGM	=   tfi


LIB_PROGRAM		=   ../flbw.a
LIB_SHA1		=	../lib/sha1
LIB_SHA256		=	../lib/sha256
LIB_SHA512		=	../lib/sha512
LIB_BASE64 		=	../lib/base64

LIBS			= 	$(LIB_PROGRAM) $(LIB_SHA1)/flbw_sha1.a $(LIB_SHA256)/flbw_sha256.a $(LIB_SHA512)/flbw_sha512.a $(LIB_BASE64)/flbw_base64.a

RM				=   -rm -f
CP				=	cp -Rf

CPPFLAGS 		=  -std=c++11

all:				make_libs $(LIB_PROGRAM) tib tibp tra tfi

tib:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_T_IB_PRGM) $(T_IB_PRGM) $(LIBS)

tibp:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_T_IBP_PRGM) $(T_IBP_PRGM) $(LIBS)

tra:				make_libs $(LIB_PROGRAM)
					$(CC) $(CPPFLAGS) -o $(NAME_T_RA_PRGM) $(T_RA_PRGM) $(LIBS)

tfi:				make_libs $(LIB_PROGRAM)
					base64 /dev/urandom | head -c 1000000 > files_integrity/files/test1.txt
					base64 /dev/urandom | head -c 5000000 > files_integrity/files/test2.txt
					base64 /dev/urandom | head -c 10000000 > files_integrity/files/test3.txt
					base64 /dev/urandom | head -c 25000000 > files_integrity/files/test4.txt
					base64 /dev/urandom | head -c 50000000 > files_integrity/files/test5.txt
					$(CC) $(CPPFLAGS) -o $(NAME_T_FI_PRGM) $(T_FI_PRGM) $(LIBS)

$(LIB_PROGRAM):		$(OBJ)
					ar rc $(LIB_PROGRAM) $(OBJ)
					ranlib $(LIB_PROGRAM)
					chmod +x $(LIB_PROGRAM)
				
make_libs:
					make -C .. all

clean:
					$(RM) $(NAME_T_IB_PRGM)
					$(RM) $(NAME_T_IBP_PRGM)
					$(RM) $(NAME_T_RA_PRGM)
					$(RM) $(NAME_T_FI_PRGM)
	
fclean:				clean
					$(RM) ./files_integrity/files/*

re:		    		fclean all

.PHONY:		    	all clean fclean re
