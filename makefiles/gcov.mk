ifeq ($(unittest), yes)
	CFLAGS		+= -D UNITTEST
	OPTIONS		+= unittest=yes
endif

ifeq ($(coverage), yes)
	OPTIONS		+= coverage=yes
	CFLAGS		+= -fprofile-arcs -ftest-coverage
	#CFLAGS += -fprofile-arcs -ftest-coverage -fkeep-inline-functions -fno-default-inline
endif
