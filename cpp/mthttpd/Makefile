#NOTE: build libevent(2.0.14) first!
#1. cd ../../3rdparty/
#2. make

TARGETS			+=	simple
TARGETS			+=	mthttpd

LLIB			+=	$(LIB)/libevent_pthreads.a
LLIB			+=	$(LIB)/libevent.a
LDFLAGS			+=	-lpthread

include ../../common.mk

ifeq ($(PLATFORM), linux)
    LDFLAGS		+=   -lrt
endif

simple: $(OBJ_DIR)/simple.o	\
	$(OBJ_DIR)/common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LLIB)

mthttpd: $(OBJ_DIR)/mthttpd.o	\
	$(OBJ_DIR)/common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LLIB)
