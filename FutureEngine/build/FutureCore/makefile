
PROJECT_ROOT = ../..
BASE_NAME = FutureCore
TARGET_TYPE = lib

include ../make/common.mk

# SOURCE FILES

PROJ_CPP_SRCS += assert.cpp
PROJ_CPP_SRCS += debug.cpp
PROJ_CPP_SRCS += log.cpp
PROJ_CPP_SRCS += heapallocator.cpp
PROJ_CPP_SRCS += mallocallocator.cpp
PROJ_CPP_SRCS += poolallocator.cpp
PROJ_CPP_SRCS += stackallocator.cpp
PROJ_CPP_SRCS += memorytracker.cpp
PROJ_CPP_SRCS += memory.cpp
PROJ_CPP_SRCS += managedobject.cpp
PROJ_CPP_SRCS += criticalsection.cpp
PROJ_CPP_SRCS += job.cpp
PROJ_CPP_SRCS += threadpool.cpp
PROJ_CPP_SRCS += thread.cpp
PROJ_CPP_SRCS += workerthread.cpp
PROJ_CPP_SRCS += null_thread.cpp

ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))
	PROJ_CPP_SRCS += win_thread.cpp
else 
ifeq ($(PLATFORM), $(filter $(PLATFORM), LINUX ANDROID MAC IPHONE))
	PROJ_CPP_SRCS += posix_thread.cpp
endif

PROJ_SYS_INC_DIRS += $(PROJECT_ROOT)/include

vpath	%.cpp	$(PROJECT_ROOT)/src/core/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/debug/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/memory/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/memory/allocators/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/memory/tracker/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/object/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/thread/criticalsection/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/thread/pool/
vpath	%.cpp	$(PROJECT_ROOT)/src/core/thread/thread/

include ../make/modulerules.mak

