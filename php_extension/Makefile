NAME				=	flbw_ext

INI_DIR				=	/etc/php/7.0/mods-available

EXTENSION_DIR		=	$(shell php-config --extension-dir)
LIB_DIR				=	/usr/lib
LIB_DIR_EXT			=	/usr/lib/flbw_ext
DIR_EXT 			=	./flbw_ext

EXTENSION 			=	${NAME}.so
INI 				=	${NAME}.ini

COMPILER			=	g++
LINKER				=	g++

COMPILER_FLAGS		=	-Wall -c -O2 -std=c++11 -fpic -o
LINKER_FLAGS		=	-shared
LINKER_DEPENDENCIES	=	-lphpcpp -Wl,-rpath=${DIR_EXT}

RM					=	rm -rf
CP					=	cp -Rf
MKDIR				=	mkdir -p
LN 					=	ln -s

CRYPTOPP_7_SO		= 	./flbw_lib/lib/cryptopp/libcryptopp.so.7.0.0
FLBW_SO				= 	./flbw_lib/flbw.so
BASE64_SO			= 	./flbw_lib/lib/base64/flbw_base64.so
LIBMY_SO			= 	./flbw_lib/lib/libmy/flbw_libmy.so

LN_CRYPTOPP_7_SO	= 	${DIR_EXT}/libcryptopp.so.7
LN_FLBW_SO			= 	${DIR_EXT}/flbw.so
LN_BASE64_SO		= 	${DIR_EXT}/flbw_base64.so
LN_LIBMY_SO			= 	${DIR_EXT}/flbw_libmy.so

SOURCES				=	$(wildcard *.cpp)
OBJECTS				=	$(SOURCES:%.cpp=%.o)

all:					make_libs ${OBJECTS} ${EXTENSION}

make_libs:				
						make -C ./PHP-CPP install
						make -C ./flbw_lib all

${EXTENSION}:			${OBJECTS}
						mkdir -p ${DIR_EXT}
						${CP} ${FLBW_SO} ${LN_FLBW_SO}
						${CP} ${CRYPTOPP_7_SO} ${LN_CRYPTOPP_7_SO}
						${CP} ${BASE64_SO} ${LN_BASE64_SO}
						${CP} ${LIBMY_SO} ${LN_LIBMY_SO}
						${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES} ${LN_CRYPTOPP_7_SO} ${LN_BASE64_SO} ${LN_FLBW_SO} ${LN_LIBMY_SO}
						${CP} ${EXTENSION} ${DIR_EXT}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

install:				all
						${CP} ${INI} ${INI_DIR}
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						${CP} ${DIR_EXT} ${LIB_DIR}

uninstall:				
						${RM} ${INI_DIR}/${INI}
						${RM} ${EXTENSION_DIR}/${EXTENSION}
						${RM} ${LIB_DIR_EXT}

clean:
						${RM} ${EXTENSION} ${OBJECTS}
						${RM} ${DIR_EXT}
						${RM} ./*.so*

fclean:					clean
						make -C ./flbw_lib fclean

ffclean:				fclean
						make -C ./PHP-CPP clean

