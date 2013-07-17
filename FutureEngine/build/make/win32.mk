
empty =
space = $(empty) $(empty)

WIN32_SDK = $(VS110COMNTOOLS)..\..\VC
PLATFORM_DIR = $(subst $(space),\$(space),$(subst \,/,$(WIN32_SDK)))
SDK_DIR = $(subst $(space),\$(space),$(subst \,/,$(DXSDK_DIR)))

SDK_INC_FLAGS += -I$(PLATFORM_DIR)\include
SDK_INC_FLAGS += -I$(SDK_DIR)\include

CC = $(PLATFORM_DIR)/bin/cl.exe
AS = $(PLATFORM_DIR)/bin/cl.exe
LD = $(PLATFORM_DIR)/bin/link.exe
AR = $(PLATFORM_DIR)/bin/lib.exe

ELF_EXTENSION = exe
LIB_EXTENSION = lib

BASE_CPP_FLAGS += /W3
BASE_CPP_FLAGS += /Oi
BASE_CPP_FLAGS += /nologo
BASE_CPP_FLAGS += /TP
BASE_CPP_FLAGS += /c
BASE_CPP_FLAGS += /Zi
BASE_CPP_FLAGS += /MP
BASE_CPP_FLAGS += /wd4345
BASE_CPP_FLAGS += /wd4351
BASE_CPP_FLAGS += /wd4627
BASE_CPP_FLAGS += /wd4996
BASE_CPP_FLAGS += /vmg

BASE_LD_FLAGS += /NOLOGO 
BASE_LD_FLAGS += /STACK:262144,262144 
BASE_LD_FLAGS += /INCREMENTAL
BASE_LD_FLAGS += /SUBSYSTEM:WINDOWS
BASE_LD_FLAGS += /DEBUG 

BASE_AR_FLAGS += /NOLOGO

BASE_LIBS +=

debug_SUFFIX = _d
debug_DEFINES = -D_DEBUG -D_WIN32_WINNT=0x0400 -DD3D_DEBUG_INFO
debug_CPP_FLAGS = /Od /Gm /MTd /Fd\"$(PROJ_TMP_DIR)/$(PLATFORM)$(debug_SUFFIX)/vc110.pdb\"
debug_LD_FLAGS = /PDB:\"$(TARGET_DIR)/$(PLATFORM)/debug/$(BASE_NAME)_vc110.pdb\" 
debug_AR_FLAGS =

profile_SUFFIX = _r
profile_DEFINES = -D_PROFILE -D_WIN32_WINNT=0x0400 -DPROFILE
profile_CPP_FLAGS = /Ox /Ob2 /Ot /GF /FD /MT /Gy /Fd\"$(PROJ_TMP_DIR)/$(PLATFORM)$(release_SUFFIX)/vc110.pdb\"
profile_LD_FLAGS = /NODEFAULTLIB:\"xapilib.lib\" /PDB:\"$(TARGET_DIR)/$(PLATFORM)/release/$(BASE_NAME)_vc110.pdb\" 
profile_AR_FLAGS =

release_SUFFIX = _f
release_DEFINES = -D_RELEASE -D_WIN32_WINNT=0x0400
release_CPP_FLAGS = /Ox /Ob2 /Ot /GF /FD /MT /Gy /Fd\"$(PROJ_TMP_DIR)/$(PLATFORM)$(final_SUFFIX)/vc110.pdb\"
release_LD_FLAGS = /PDB:\"$(TARGET_DIR)/$(PLATFORM)/final/$(BASE_NAME)_vc110.pdb\" 
release_AR_FLAGS =


PLATFORM_BASENAME_LIBS	+= d3dx9
PLATFORM_BASENAME_LIBS	+= d3dx10
PLATFORM_BASENAME_LIBS	+= d3dx11

PLATFORM_LIBS		+= user32.lib
PLATFORM_LIBS		+= d2d1.lib
PLATFORM_LIBS		+= d3d9.lib
PLATFORM_LIBS		+= d3d10.lib
PLATFORM_LIBS		+= d3d10_1.lib
PLATFORM_LIBS		+= d3d11.lib
PLATFORM_LIBS		+= dinput8.lib
PLATFORM_LIBS		+= dxgi.lib
PLATFORM_LIBS		+= dxguid.lib
PLATFORM_LIBS		+= winmm.lib

PLATFORM_WIN32_DEFINES		+= -DWINDOWS
PLATFORM_WIN32_DEFINES		+= -D_WINDOWS
PLATFORM_PWIN32_DEFINES		+= -DUNICODE
PLATFORM_WIN32_DEFINES		+= -D_UNICODE
PLATFORM_WIN32_DEFINES		+= -DWIN32
PLATFORM_WIN32_INC_FLAGS	+= $(SDK_INC_FLAGS)

debug_PLATFORM_WIN32_LIBS		+= $(PLATFORM_LIBS) $(subst ;,\$(space), $(addsuffix d.lib, $(subst \$(space),;,$(PLATFORM_BASENAME_LIBS) $(NOPROFILE_BASENAME_LIBS))))
profile_PLATFORM_WIN32_LIBS		+= $(PLATFORM_LIBS) $(PROFILE_PLATFORM_LIBS) $(subst ;,\$(space), $(addsuffix .lib, $(subst \$(space),;,$(PLATFORM_BASENAME_LIBS))))
release_PLATFORM_WIN32_LIBS		+= $(PLATFORM_LIBS) $(subst ;,\$(space), $(addsuffix .lib, $(subst \$(space),;,$(PLATFORM_BASENAME_LIBS) $(NOPROFILE_BASENAME_LIBS))))

PLATFORM_PC_LD_FLAGS	+= /LIBPATH:\"$(WIN32_SDK)\\lib\"
PLATFORM_PC_LD_FLAGS	+= /LIBPATH:\"$(DXSDK_DIR)\\lib\\x86\"
