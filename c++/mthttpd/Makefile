TARGETS			+=	mthttpd

LLIB			+=	$(LIB)/libevent.a

include ../../common.mk

mthttpd: $(OBJ_DIR)/mthttp.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LLIB)
