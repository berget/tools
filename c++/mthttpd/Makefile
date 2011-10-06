TARGETS			+=	simple
TARGETS			+=	mthttpd

LLIB			+=	$(LIB)/libevent_pthreads.a
LLIB			+=	$(LIB)/libevent_core.a
LLIB			+=	$(LIB)/libevent_extra.a
LDFLAGS			+=	-lpthread

include ../../common.mk

simple: $(OBJ_DIR)/simple.o	\
	$(OBJ_DIR)/common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LLIB)

mthttpd: $(OBJ_DIR)/mthttpd.o	\
	$(OBJ_DIR)/common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LLIB)
