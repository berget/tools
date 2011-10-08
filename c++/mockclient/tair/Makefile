TARGETS			+=	libtairclientapi$(STATIC_LIB_EXT)
TARGETS			+=	libtairclientapi$(SHARED_LIB_EXT)

CXXFILES		+=	tair_client_api.cpp

include ../../../common.mk

install:
	cp -f tair_client_api.hpp define.hpp /usr/local/include
	cp -f libtairclientapi$(SHARED_LIB_EXT) /usr/local/lib
