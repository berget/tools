TARGETS			+=	libkagent$(STATIC_LIB_EXT)
TARGETS			+=	libkagent$(SHARED_LIB_EXT)

CXXFILES		+=	Kagent.cpp

include ../../../common.mk

install:
	cp -f Kagent.h /usr/local/include
	cp -f libkagent$(SHARED_LIB_EXT) /usr/local/lib
