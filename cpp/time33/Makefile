TARGETS				+=	benchmark
TARGETS				+=	regress
TARGETS				+=	test
TARGETS				+=	lconvert
TARGETS				+=	cconvert
TARGETS				+=	hconvert

include ../../common.mk

benchmark:						\
	$(OBJ_DIR)/benchmark.o		\
	$(OBJ_DIR)/hash.o			\
	$(OBJ_DIR)/common.o
	$(CC) $(LDFLAGS) $^ -o $@

regress:						\
	$(OBJ_DIR)/regress.o		\
	$(OBJ_DIR)/hash.o			\
	$(OBJ_DIR)/common.o
	$(CC) $(LDFLAGS) $^ -o $@

test: $(OBJ_DIR)/test.o
	$(CC) $(LDFLAGS) $^ -o $@

lconvert:						\
	$(OBJ_DIR)/lconvert.o		\
	$(OBJ_DIR)/hash.o			\
	$(OBJ_DIR)/common.o
	$(CC) $(LDFLAGS) $^ -o $@

cconvert:						\
	$(OBJ_DIR)/cconvert.o		\
	$(OBJ_DIR)/hash.o			\
	$(OBJ_DIR)/common.o
	$(CC) $(LDFLAGS) $^ -o $@

hconvert:						\
	$(OBJ_DIR)/hconvert.o		\
	$(OBJ_DIR)/hash.o			\
	$(OBJ_DIR)/common.o
	$(CC) $(LDFLAGS) $^ -o $@
