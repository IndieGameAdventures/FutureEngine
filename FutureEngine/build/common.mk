
T=bin

.SILENT:

ifeq ($(origin PROJECT_ROOT), undefined)
$(error PROJECT_ROOT is not set)
endif

ifeq ($(origin BASE_NAME), undefined)
$(error BASE_NAME is not set)
endif

ifeq ($(origin TARGET_TYPE), undefined)
$(error TARGET_TYPE is not set)
endif

TARGET_PLATFORMS = WIN32 LINUX ANDROID

PLATFORM ?= WIN32

PLATFORM_LOWERCASE = $(shell echo $(PLATFORM) | tr [A-Z] [a-z])
PROJECT_ROOT_FIXED = $(subst $(space),\$(space),$(subst \,/,$(PROJECT_ROOT)))

# PROJECT TEMP FOLDER

ROOT_TMP_DIR = $(PROJECT_ROOT_FIXED)/tmp
PROJ_TMP_DIR = $(ROOT_TMP_DIR)/$(BASE_NAME)

VER_TMP_DIR = $(PROJ_TMP_DIR)/$(VER_DIR)
VER_DEP_DIR = $(VER_TMP_DIR)/deps

# General options

PROJ_BIN_DIR = $(PROJECT_ROOT_FIXED)/bin
PROJ_LIB_DIR = $(PROJECT_ROOT_FIXED)/lib

PLATFORM_TARGET_DIR = $(TARGET_DIR)/$(PLATFORM_LOWERCASE)
VER_TARGET_DIR = $(PLATFORM_TARGET_DIR)/$(VERSION)

ifeq ($(TARGET_TYPE),elf)
TARGET_DIR = $(PROJ_BIN_DIR)
VER_ELF	?= $(VER_TARGET_DIR)/$(BASE_NAME).$(ELF_EXTENSION)
endif

ifeq ($(TARGET_TYPE),lib)
TARGET_DIR = $(PROJ_LIB_DIR)
VER_LIB	?= $(VER_TARGET_DIR)/$(BASE_NAME).$(LIB_EXTENSION)
endif

# General make flags
#
# --no-print-directory		= don't print entering-leaving subdir messages
# --no-builtin-rules		= disable the built-in implicit rules
# --no-builtin-variables	= disable the built-in variable settings

BASE_MFLAGS += --no-print-directory
BASE_MFLAGS += --no-builtin-rules
BASE_MFLAGS += --no-builtin-variables
BASE_MFLAGS += -j4

# General defines

BASE_DEFINES += -D_PLATFORM_$(PLATFORM)

# Default to no scaleform and no fmod support
# Don't like these here, but the only way to get it into game makefiles without them copying it

#ifeq ($(PLATFORM), $(filter $(PLATFORM), PSP))
#NO_FMOD 	?= 1
#endif

ifeq ($(PLATFORM), $(filter $(PLATFORM), PSP PS3))
NO_SCALEFORM 	?= 1
endif

#ifeq ($(PLATFORM), $(filter $(PLATFORM), PS3))
#NO_LUA 	?= 1
#endif

#ifeq ($(PLATFORM), $(filter $(PLATFORM), PS3))
#NO_GAMEDBG	?= 1
#endif

ifeq ($(NO_FMOD), 1)
BASE_DEFINES += -D_NO_FMOD
endif

ifeq ($(NO_SCALEFORM), 1)
BASE_DEFINES += -D_NO_SCALEFORM
endif

ifeq ($(NO_LUA), 1)
BASE_DEFINES += -D_NO_LUA
endif

ifeq ($(NO_GAMEDBG), 1)
BASE_DEFINES += -D_NO_GAMEDBG
endif

ifneq ($(origin PROGRAMMER), undefined)
BASE_DEFINES += -D$(PROGRAMMER)=1
endif

# Bullet physics support

BASE_DEFINES += -DBT_OMICRON
BASE_DEFINES += -DBT_NO_PROFILE
BASE_DEFINES += -DBT_HAS_ALIGNED_ALLOCATOR
#BASE_DEFINES += -DBT_USE_DOUBLE_PRECISION

ifeq ($(PROFILE_OBJ_PERF), 1)
BASE_DEFINES += -DPROFILE_OBJ_PERF
endif

# Version specific flags

TARGET_VERSIONS = debug release final


include $(OMICRON_ROOT)/code/make/commondefs.$(PLATFORM)

