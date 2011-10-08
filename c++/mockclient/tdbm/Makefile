TARGETS			+=	libtdbm$(STATIC_LIB_EXT)
TARGETS			+=	libtdbm$(SHARED_LIB_EXT)

CXXFILES		+=	tdbm.cpp

include ../../../common.mk

install:
	cp -f tdbm.h /usr/local/include
	cp -f libtdbm$(SHARED_LIB_EXT) /usr/local/lib
