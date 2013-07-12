
PROJECT_ROOT = ../../
BASE_NAME = FutureCore
TARGET_TYPE = lib

include ../common.mk

ifeq ($(PLATFORM),360)
PROJ_CC_FLAGS += /wd4985
endif

# DEFINES

PROJ_DEFINES += -DOMICRON_LIBRARY

# SOURCE FILES

PROJ_CPP_SRCS += alloc.cpp
PROJ_CPP_SRCS += criticalsection.cpp
PROJ_CPP_SRCS += debug.cpp
PROJ_CPP_SRCS += endian.cpp
PROJ_CPP_SRCS += err.cpp
PROJ_CPP_SRCS += genhelper.cpp
PROJ_CPP_SRCS += language.cpp
PROJ_CPP_SRCS += microheap.cpp
PROJ_CPP_SRCS += thread.cpp

# PROJECT INCLUDES

PROJ_SYS_INC_DIRS += $(OMICRON_ROOT)/code/include

# Where to look for files

vpath	%.cpp	./
vpath	%.cpp	./$(PLATFORM_LOWERCASE)

include $(OMICRON_ROOT)/code/make/modulerules.mak

