
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

BASE_DEFINES += -D_$(PLATFORM)

# Version specific flags

TARGET_VERSIONS = debug release final


include $(PROJECT_ROOT)/build/make/$(PLATFORM_LOWERCASE).mk

