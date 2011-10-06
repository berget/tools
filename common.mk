PROJECT_ROOT	:=	$(shell cd $(dir $(lastword $(MAKEFILE_LIST))); pwd)

CODE			?=	c++
COMPILER		?=	gcc

include $(PROJECT_ROOT)/makefiles/command.mk
include $(PROJECT_ROOT)/makefiles/variable.mk
include $(PROJECT_ROOT)/makefiles/gcov.mk

include $(PROJECT_ROOT)/makefiles/rules/rules.mk

INCLUDE		+=	-I$(INC)
INCLUDE		+=	-I$(PROJECT_ROOT)/src
LDFLAGS		+=	-L$(LIB)

include $(PROJECT_ROOT)/makefiles/$(COMPILER)/$(CODE).mk
include $(PROJECT_ROOT)/makefiles/platform/$(PLATFORM).mk

# coverage in unittest
CLEAN_LIST	+=	coverage.info
