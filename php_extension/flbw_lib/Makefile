CC				=   g++

NAME			=   flbw
NAME_ST_LIB		=   $(NAME).a
NAME_DYN_LIB	=   $(NAME).so

LIB_SHA1		=	./lib/sha1
LIB_SHA256		=	./lib/sha256
LIB_SHA512		=	./lib/sha512
LIB_BASE64		=	./lib/base64

SRC =				./flbw.cpp

OBJ				=   $(SRC:%.cpp=%.o)

LN				= 	ln -sf
RM				=   -rm -f

CXXFLAGS		=	-Wall -Wpedantic -fPIC -std=c++11

all:				make_libs base64_dynamic base64_static

base64_dynamic: 	$(OBJ)
					${LN} $(LIB_SHA1)/flbw_sha1.so ./
					${LN} $(LIB_SHA256)/flbw_sha256.so ./
					${LN} $(LIB_SHA512)/flbw_sha512.so ./
					${LN} $(LIB_BASE64)/flbw_base64.so ./
					$(CC) -shared $(OBJ) $(CXXFLAGS) -o $(NAME_DYN_LIB) flbw_sha1.so flbw_sha256.so flbw_sha512.so flbw_base64.so
	
base64_static:  	$(OBJ)
					ar rc $(NAME_ST_LIB) $(OBJ)
					ranlib $(NAME_ST_LIB)

make_libs:
					make -C $(LIB_SHA1) all
					make -C $(LIB_SHA256) all
					make -C $(LIB_SHA512) all
					make -C $(LIB_BASE64) all

re:		    		fclean all

clean:	
					$(RM) $(OBJ)
					$(RM) $(NAME_ST_LIB)
					$(RM) $(NAME_DYN_LIB)
	
fclean:				clean
					$(RM) $(NAME_ST_LIB) $(NAME_DYN_LIB)
					make -C $(LIB_SHA1) clean
					make -C $(LIB_SHA256) clean
					make -C $(LIB_SHA512) clean
					make -C $(LIB_BASE64) fclean
					${RM} ./*.so*

.PHONY:		    	all base64_dynamic base64_static clean fclean re