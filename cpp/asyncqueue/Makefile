PROJECT_ROOT   	= 	$(shell cd .; pwd)

TARGETS			+=	asyncqueue

CFLAGS			+=	-lpthread

include $(PROJECT_ROOT)/common.mk

# 自定义的targets编译规则
asyncqueue: $(OBJ_DIR)/main.o	\
	$(OBJ_DIR)/asyncqueue.o
	$(CC) $(CFLAGS) -o $@ $^
