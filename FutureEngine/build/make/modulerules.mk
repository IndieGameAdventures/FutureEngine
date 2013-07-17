
PROJ_INC_FLAGS = $(addprefix -iquote,$(PROJ_INC_DIRS)

PROJ_SYS_INC_FLAGS = $(addprefix -I,$(PROJ_SYS_INC_DIRS))

C_OBJS			= $(subst .cpp,.o,$(PROJ_CPP_SRCS)) $(subst .c,.o,$(PROJ_C_SRCS))
VER_C_OBJS		= $(addprefix $(VER_TMP_DIR)/,$(C_OBJS))

FULL_OBJS		+= $(VER_C_OBJS)

FULL_INC_FLAGS_LIST += $(PROJ_INC_FLAGS)
FULL_INC_FLAGS_LIST += $(BASE_INC_FLAGS)
FULL_INC_FLAGS_LIST += $(PLATFORM_INC_FLAGS)
FULL_INC_FLAGS_LIST += $(PROJ_SYS_INC_FLAGS)

ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))
PATH_FIX_0 = $(subst \$(space),;,$(FULL_INC_FLAGS_LIST))
PATH_FIX_1 = $(patsubst -I%,-I "%", $(subst -iquote,-I, $(PATH_FIX_0)))
PATH_FIX_2 = $(subst /,\, $(subst ;,$(space), $(PATH_FIX_1)))
FULL_INC_FLAGS = $(subst -I,/I, $(PATH_FIX_2))
else
FULL_INC_FLAGS = $(FULL_INC_FLAGS_LIST)
endif

FULL_DEFINES_LIST += $(BASE_DEFINES)
FULL_DEFINES_LIST += $(VER_DEFINES)
FULL_DEFINES_LIST += $(PLATFORM_DEFINES)
FULL_DEFINES_LIST += $(PROJ_DEFINES)

ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))
FULL_DEFINES = $(patsubst -D%,/D "%", $(FULL_DEFINES_LIST))
else
FULL_DEFINES = $(FULL_DEFINES_LIST)
endif

FULL_LIBS_LIST += $(PROJ_LIBS)
FULL_LIBS_LIST += $(PLATFORM_VER_LIBS)
FULL_LIBS_LIST += $(PLATFORM_LIBS)
FULL_LIBS_LIST += $(BASE_LIBS)

FULL_LIBS = $(FULL_LIBS_LIST)

ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))
LIB_PATH_FIX_0 = $(subst \$(space),;,$(FULL_LIBS_LIST))
LIB_PATH_FIX_1 = $(addsuffix ", $(addprefix ", $(LIB_PATH_FIX_0)))
FULL_LIBS_LINK = $(subst /,\, $(subst ;,$(space), $(LIB_PATH_FIX_1)))
else
FULL_LIBS_LINK = $(FULL_LIBS)
endif

FULL_CC_FLAGS += $(BASE_CPP_FLAGS)
FULL_CC_FLAGS += $(VER_CPP_FLAGS)
FULL_CC_FLAGS += $(PLATFORM_CPP_FLAGS)
FULL_CC_FLAGS += $(PROJ_CC_FLAGS)
FULL_CC_FLAGS += $(FULL_INC_FLAGS)
FULL_CC_FLAGS += $(FULL_DEFINES)

FULL_AS_FLAGS += $(PROJ_AS_FLAGS)
FULL_AS_FLAGS += $(VER_AS_FLAGS)
FULL_AS_FLAGS += $(PLATFORM_AS_FLAGS)
FULL_AS_FLAGS += $(BASE_AS_FLAGS)

FULL_LD_FLAGS += $(PROJ_LD_FLAGS)
FULL_LD_FLAGS += $(VER_LD_FLAGS)
FULL_LD_FLAGS += $(PLATFORM_LD_FLAGS)
FULL_LD_FLAGS += $(BASE_LD_FLAGS)

FULL_AR_FLAGS += $(PROJ_AR_FLAGS)
FULL_AR_FLAGS += $(VER_AR_FLAGS)
FULL_AR_FLAGS += $(PLATFORM_AR_FLAGS)
FULL_AR_FLAGS += $(BASE_AR_FLAGS)

.PHONY: debug profile release clean bin clean_proj

default: debug

debug profile release:
	$(MAKE) $(MFLAGS) $(BASE_MFLAGS) $(T) \
			VERSION="$@" \
			VER_DIR="$(PLATFORM)$($@_SUFFIX)" \
			VER_DEFINES="$($@_DEFINES)" \
			VER_CPP_FLAGS="$($@_CPP_FLAGS)" \
			VER_AS_FLAGS="$($@_AS_FLAGS)" \
			VER_LD_FLAGS="$($@_LD_FLAGS)" \
			VER_AR_FLAGS="$($@_AR_FLAGS)" \
			PLATFORM_DEFINES="$(PLATFORM_$(PLATFORM)_DEFINES)" \
			PLATFORM_LIBS="$(PLATFORM_$(PLATFORM)_LIBS)" \
			PLATFORM_VER_LIBS="$($@_PLATFORM_$(PLATFORM)_LIBS)" \
			PLATFORM_CPP_FLAGS="$(PLATFORM_$(PLATFORM)_CPP_FLAGS)" \
			PLATFORM_INC_FLAGS="$(PLATFORM_$(PLATFORM)_INC_FLAGS)" \
			PLATFORM_AS_FLAGS="$(PLATFORM_$(PLATFORM)_AS_FLAGS)" \
			PLATFORM_LD_FLAGS="$(PLATFORM_$(PLATFORM)_LD_FLAGS)" \
			PLATFORM_AR_FLAGS="$(PLATFORM_$(PLATFORM)_AR_FLAGS)"

ifeq ($(VERSION),)
clean:
	for cleanver in $(TARGET_VERSIONS) ; do \
		$(MAKE) $$cleanver T="clean" ; \
	done
else
clean: clean_proj
	echo Cleaning $(VERSION)...
	rm -rf $(VER_TMP_DIR)
	rm -f $(VER_ELF)
	rm -f $(VER_LIB)
endif

bin:  $(VER_ELF) $(VER_LIB)

ifneq ($(VERSION),)
$(TARGET_DIR) $(ROOT_TMP_DIR):
	echo Making directory $@...
	mkdir $(subst /,\,$@)

$(PLATFORM_TARGET_DIR) $(PROJ_TMP_DIR): | $(TARGET_DIR) $(ROOT_TMP_DIR)
	echo Making directory $@...
	mkdir $(subst /,\,$@)

$(VER_TARGET_DIR) $(VER_TMP_DIR): | $(PLATFORM_TARGET_DIR) $(PROJ_TMP_DIR)
	echo Making directory $@...
	mkdir $(subst /,\,$@)

$(VER_DEP_DIR): | $(VER_TMP_DIR)
	echo Making directory $@...
	mkdir $(subst /,\,$@)
endif

$(VER_ELF): $(FULL_OBJS) $(FULL_LIBS) $(CNT_FILES_DEP)
	echo Linking $(VER_ELF)...

ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))
	$(LD) $(FULL_LD_FLAGS) $(FULL_OBJS) $(FULL_LIBS_LINK) /OUT:"$(VER_ELF)"
endif
else
	$(LD) $(FULL_OBJS) $(FULL_LIBS_LINK) $(FULL_LD_FLAGS) -o $(VER_ELF)
endif

$(VER_LIB): $(FULL_OBJS)
	echo Creating library $(VER_LIB)...
ifeq ($(PLATFORM),WII)
	$(AR) $(FULL_AR_FLAGS) $(FULL_OBJS) -o $(VER_LIB)
else
ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))
	rm -f $@
	$(AR) $(FULL_AR_FLAGS) $(FULL_OBJS) /OUT:"$(VER_LIB)"
else
	rm -f $@
	$(AR) $(FULL_AR_FLAGS) $(VER_LIB) $(FULL_OBJS)
endif
endif

$(FULL_OBJS) $(FULL_LIBS): | $(TARGET_DIR) $(PLATFORM_TARGET_DIR) $(VER_TARGET_DIR) $(ROOT_TMP_DIR) $(PROJ_TMP_DIR) $(VER_TMP_DIR) $(VER_DEP_DIR)

$(VER_TMP_DIR)/%.o: %.cpp
	echo Compiling $(VERSION) $(<F)...
ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))

	$(CC) $(FULL_CC_FLAGS) /Fo"$@" $<
	$(CC) $(FULL_CC_FLAGS) /showIncludes /EP $< 2> $(VER_TMP_DIR)/$(notdir $*).d 1>$(VER_TMP_DIR)/$(notdir $*).nil
	rm -f $(VER_TMP_DIR)/$(notdir $*).nil
	echo $@: $$\(wildcard $< \\ > $(VER_DEP_DIR)/$(notdir $*).d
	sed \
		-e '/Note: including file:/!d' \
		-e 's/.*Note: including file:[ \t]*/\t/' \
		-e 'sX\\X/Xg' \
		-e 'sX\"XXg' \
		-e 'sX/\ X\\ Xg' \
		-e 'sX:\\X: Xg' \
		-e 's/$$/ \\/' \
		< $(VER_TMP_DIR)/$(notdir $*).d >> $(VER_DEP_DIR)/$(notdir $*).d
	echo \) >> $(VER_DEP_DIR)/$(notdir $*).d
	rm -f $(VER_TMP_DIR)/$(notdir $*).d
else
	$(CC) $(FULL_CC_FLAGS) $< -o $@
	sed \
		-e 'sX\\X/Xg' \
		-e 'sX\"XXg' \
		-e 'sX/\ X\\ Xg' \
		-e 'sX:\\X: Xg' \
		-e 'sX/$$X \\Xg' \
		-e 'sX.*o:X$(VER_TMP_DIR)/$*.o:Xg' \
		< $(VER_TMP_DIR)/$(notdir $*).d > $(VER_DEP_DIR)/$(notdir $*).d
	sed \
		-e 'sX\\X/Xg' \
		-e 'sX\"XXg' \
		-e 'sX/\ X\\ Xg' \
		-e 'sX:\\X: Xg' \
		-e 'sX/$$X \\Xg' \
		-e 's/.*: \+//' \
		-e 's/\ *\\$$//' \
		-e 's/^[ \t]*//' \
		-e '/^$$/ d' \
		-e 's/$$/ :/' \
		< $(VER_TMP_DIR)/$(notdir $*).d >> $(VER_DEP_DIR)/$(notdir $*).d
	rm -f $(VER_TMP_DIR)/$(notdir $*).d
endif

$(VER_TMP_DIR)/%.o: %.c
	echo Compiling $(VERSION) $(<F)...
ifeq ($(PLATFORM), $(filter $(PLATFORM), WIN32 WIN64 WIN8 WINPHONE))
	$(CC) $(FULL_CC_FLAGS) /Fo"$@" $<
	$(CC) $(FULL_CC_FLAGS) /showIncludes /EP $< 2> $(VER_TMP_DIR)/$(notdir $*).d 1>$(VER_TMP_DIR)/$(notdir $*).nil
	rm -f $(VER_TMP_DIR)/$(notdir $*).nil
	echo $@: $$\(wildcard $< \\ > $(VER_DEP_DIR)/$(notdir $*).d
	sed \
		-e '/Note: including file:/!d' \
		-e 's/.*Note: including file:[ \t]*/\t/' \
		-e 'sX\\X/Xg' \
		-e 'sX\"XXg' \
		-e 'sX/\ X\\ Xg' \
		-e 'sX:\\X: Xg' \
		-e 's/$$/ \\/' \
		< $(VER_TMP_DIR)/$(notdir $*).d >> $(VER_DEP_DIR)/$(notdir $*).d
	echo \) >> $(VER_DEP_DIR)/$(notdir $*).d
	rm -f $(VER_TMP_DIR)/$(notdir $*).d
else
	$(CC) $(FULL_CC_FLAGS) $< -o $@
	sed \
		-e 'sX\\X/Xg' \
		-e 'sX\"XXg' \
		-e 'sX/\ X\\ Xg' \
		-e 'sX:\\X: Xg' \
		-e 'sX/$$X \\Xg' \
		-e 'sX.*o:X$(VER_TMP_DIR)/$*.o:Xg' \
		< $(VER_TMP_DIR)/$(notdir $*).d > $(VER_DEP_DIR)/$(notdir $*).d
	sed \
		-e 'sX\\X/Xg' \
		-e 'sX\"XXg' \
		-e 'sX/\ X\\ Xg' \
		-e 'sX:\\X: Xg' \
		-e 'sX/$$X \\Xg' \
		-e 's/.*: \+//' \
		-e 's/\ *\\$$//' \
		-e 's/^[ \t]*//' \
		-e '/^$$/ d' \
		-e 's/$$/ :/' \
		< $(VER_TMP_DIR)/$(notdir $*).d >> $(VER_DEP_DIR)/$(notdir $*).d
	rm -f $(VER_TMP_DIR)/$(notdir $*).d
endif

ifneq ($(VERSION),)
ifeq ($(filter %clean, $(T)),)
-include $(addprefix $(VER_DEP_DIR)/,$(PROJ_CPP_SRCS:.cpp=.d) $(PROJ_C_SRCS:.c=.d))
endif
endif
