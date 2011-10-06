TARGETS			+=	simple

LLIB			+=	$(LIB)/libevent.a

include ../../common.mk

simple: $(OBJ_DIR)/simple.o	\
	$(OBJ_DIR)/common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LLIB)
