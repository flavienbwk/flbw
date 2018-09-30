NAME				=	flbw_ext

INI_DIR				=	/etc/php/7.0/mods-available
PHP_INI_CLI			=	${INI_DIR}/../cli/php.ini
PHP_INI_FPM			=	${INI_DIR}/../fpm/php.ini
PHP_INI_INSTRUCT	=	extension=flbw_ext.so

EXTENSION_DIR		=	$(shell php-config --extension-dir)
LIB_DIR				=	/usr/lib
LIB_DIR_EXT			=	/usr/lib/flbw_ext

EXTENSION 			=	${NAME}.so
INI 				=	${NAME}.ini

COMPILER			=	g++
LINKER				=	g++

COMPILER_FLAGS		=	-Wall -c -O2 -std=c++11 -fpic -o
LINKER_FLAGS		=	-shared
LINKER_DEPENDENCIES	=	-lphpcpp -Wl,-rpath=${LIB_DIR_EXT}

RM					=	rm -rf
CP					=	cp -Rf
MKDIR				=	mkdir -p
LN 					=	ln -s

SHA1_SO				= 	./flbw_lib/lib/sha1/flbw_sha1.so
SHA256_SO			= 	./flbw_lib/lib/sha256/flbw_sha256.so
SHA512_SO			= 	./flbw_lib/lib/sha512/flbw_sha512.so
FLBW_SO				= 	./flbw_lib/flbw.so
BASE64_SO			= 	./flbw_lib/lib/base64/flbw_base64.so

LN_SHA1_SO			= 	${LIB_DIR_EXT}/flbw_sha1.so
LN_SHA256_SO		= 	${LIB_DIR_EXT}/flbw_sha256.so
LN_SHA512_SO		= 	${LIB_DIR_EXT}/flbw_sha512.so
LN_FLBW_SO			= 	${LIB_DIR_EXT}/flbw.so
LN_BASE64_SO		= 	${LIB_DIR_EXT}/flbw_base64.so

SOURCES				=	$(wildcard *.cpp)
OBJECTS				=	$(SOURCES:%.cpp=%.o)

all:					make_libs ${OBJECTS} ${EXTENSION}

make_libs:				
						make -C ./PHP-CPP
						make -C ./PHP-CPP install
						make -C ./flbw_lib all

${EXTENSION}:			${OBJECTS}
						${MKDIR} ${LIB_DIR_EXT}
						${CP} ${FLBW_SO} ${LN_FLBW_SO}
						${CP} ${SHA1_SO} ${LN_SHA1_SO}
						${CP} ${SHA256_SO} ${LN_SHA256_SO}
						${CP} ${SHA512_SO} ${LN_SHA512_SO}
						${CP} ${BASE64_SO} ${LN_BASE64_SO}
						${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES} ${LN_SHA1_SO} ${LN_SHA256_SO} ${LN_SHA512_SO} ${LN_BASE64_SO} ${LN_FLBW_SO}
						${CP} ${EXTENSION} ${LIB_DIR_EXT}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

install:				re
						${CP} ${INI} ${INI_DIR}
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						perl -pi.bak -we 's/${PHP_INI_INSTRUCT}[\r\n]+//g' ${PHP_INI_CLI}
						perl -pi.bak -we 's/${PHP_INI_INSTRUCT}[\r\n]+//g' ${PHP_INI_FPM}
						echo "${PHP_INI_INSTRUCT}" >> ${PHP_INI_CLI}
						echo "${PHP_INI_INSTRUCT}" >> ${PHP_INI_FPM}

uninstall:				
						${RM} ${INI_DIR}/${INI}
						${RM} ${EXTENSION_DIR}/${EXTENSION}
						${RM} ${LIB_DIR_EXT}
						perl -pi.bak -we 's/${PHP_INI_INSTRUCT}[\r\n]+//g' ${PHP_INI_CLI}
						perl -pi.bak -we 's/${PHP_INI_INSTRUCT}[\r\n]+//g' ${PHP_INI_FPM}

re:		    			fclean all

clean:
						${RM} ${EXTENSION} ${OBJECTS}
						${RM} ./*.so*

fclean:					clean
						make -C ./flbw_lib fclean

ffclean:				fclean
						make -C ./PHP-CPP clean

