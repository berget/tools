ifndef PROJECT_ROOT
    $(error Enviroment variable PROJECT_ROOT is not set, quitting ...)
endif

CC			=	g++ -ggdb -D_LINUX_ -Wall
INC			=	$(PROJECT_ROOT)/include
LIB			=	$(PROJECT_ROOT)/libs
SRC			=	$(PROJECT_ROOT)/src
DOC			=	$(PROJECT_ROOT)/doc

CFLAGS		+=		# init as empty

LLIB		+=	

SUBDIRS		+=	

OBJ_DIR		=	.obj
SOBJ_DIR	=	.sharedobj
TOBJ_DIR	=	.testobj
MKDIRS		=	$(OBJ_DIR) $(SOBJ_DIR) $(TOBJ_DIR) $(LIB)

OFILES		=	$(CXXFILES:%.cpp=$(OBJ_DIR)/%.o)
SOFILES		=	$(CXXFILES:%.cpp=$(SOBJ_DIR)/%.o)
TOFILES		=	$(CXXFILES:%.cpp=$(TOBJ_DIR)/%.o)
PREREQS		+=
CLEANFILES	+=
CLEANDIRS	+=

# automatic variable
PROCESSOR	=	$(shell uname -m)
ARCH		=
ifeq ($(PROCESSOR), x86_64)
	ARCH	=	64
endif
ifeq ($(PROCESSOR), i386)
	ARCH	=
endif

# ruls
.PHONY: all clean debug runtest
all: prereq $(TARGETS)
	@echo "completed: $(TARGETS)"

prereq: $(PREREQS)
	for dir in $(SUBDIRS); do	\
		make -C $$dir all;	\
	done

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) -c $(INCLUDE) $^ -o $@
$(SOBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) -fPIC -c $(INCLUDE) $^ -o $@

.SECONDARY: $(OFILES) $(SOFILES) $(TOFILES)

%.a: $(OFILES)	| $(LIB)
	@echo "Generating static library: $@ ..."
	ar rcv $(LIB)/$@ $^
	mkdir -p $(INC)/athena
	cp -rf $(PROJECT_ROOT)/src/*.h $(INC)/athena/
	@echo "$@ is ready."

%.so: $(SOFILES)
	@echo "Generating shared library: $@ ..."
	$(CC) -shared $^ -o $@
	@echo "$@ is ready."

$(sort $(MKDIRS)):
	mkdir -p $@

clean:
	for dir in $(SUBDIRS); do	\
		make -C $$dir clean;	\
	done
	@echo "clean all ..."
	rm -f *.o *.so *.a *.pyc
	rm -f $(PROJECT_ROOT)/libs/*.a
	rm -f $(PROJECT_ROOT)/libs/*.so
	@echo "remove object files ..."
	rm -rf $(OBJ_DIR) $(SOBJ_DIR) $(TOBJ_DIR)
	@echo "remove target files ..."
	rm -rf $(TARGETS)
	@echo "remove cleanfiles ..."
	rm -f $(CLEANFILES)
	@echo "remove cleandirs ..."
	rm -rf $(CLEANDIRS)

debug:
	@echo "PROJECT_ROOT: $(PROJECT_ROOT)"
	@echo "TARGETS: $(TARGETS)"
	@echo "OFILES: $(OFILES)"
	@echo "INC: $(INC)"
	@echo "LIB: $(LIB)"
	@echo "LLIB: $(LLIB)"
	@echo "INCLUDE: $(INCLUDE)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "ARCH: $(ARCH)"
