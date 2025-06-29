# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Adrian "asie" Siekierka, 2023

WONDERFUL_TOOLCHAIN ?= /opt/wonderful
TARGET ?= wswan/medium
include $(WF_TARGET_DIR)/makedefs.mk

PYTHON3 ?= python3

# Source code paths
# -----------------

INCLUDEDIRS	:= include src/include
SOURCEDIRS	:= src

ANK_FONT  := assets/unscii.png
SJIS_FONT := assets/misaki_gothic_2nd.png

# Defines passed to all files
# ---------------------------

DEFINES		:= -DLIBWS_API_COMPAT=202504L

# Libraries
# ---------

LIBDIRS		:= $(WF_ARCH_LIBDIRS)

# Build artifacts
# ---------------

NAME		:= wwcl
BUILDDIR	:= build/$(TARGET)
ARCHIVE		:= $(BUILDDIR)/lib$(NAME).a

# Verbose flag
# ------------

ifeq ($(V),1)
_V		:=
else
_V		:= @
endif

# Source files
# ------------

SOURCES_S	:= $(shell find -L $(SOURCEDIRS) -name "*.s")
SOURCES_C	:= $(shell find -L $(SOURCEDIRS) -name "*.c")

# Compiler and linker flags
# -------------------------

WARNFLAGS	:= -Wall

INCLUDEFLAGS	:= $(foreach path,$(INCLUDEDIRS),-I$(path)) \
		   $(foreach path,$(LIBDIRS),-I$(path)/include)

ASFLAGS		+= -x assembler-with-cpp $(DEFINES) $(WF_ARCH_CFLAGS) \
		   $(INCLUDEFLAGS) -ffunction-sections -fdata-sections

CFLAGS		+= -std=gnu11 $(WARNFLAGS) $(DEFINES) $(WF_ARCH_CFLAGS) \
		   $(INCLUDEFLAGS) -ffunction-sections -fdata-sections \
		   -O2 -fno-jump-tables -g

# Intermediate build files
# ------------------------

OBJS_SOURCES	:= $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(SOURCES_S))) \
		   $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(SOURCES_C)))

OBJS		:= $(OBJS_SOURCES)

DEPS		:= $(OBJS:.o=.d)

# Targets
# -------

.PHONY: all clean doc install

all: $(ARCHIVE) compile_commands.json

$(ARCHIVE): $(OBJS)
	@echo "  AR      $@"
	@$(MKDIR) -p $(@D)
	$(_V)$(AR) rcs $@ $(OBJS)

clean:
	@echo "  CLEAN"
	$(_V)$(RM) $(ARCHIVE) $(BUILDDIR)

doc:
	@echo "  MKDIR    build/doc"
	$(_V)$(MKDIR) -p build/doc
	@echo "  DOXYGEN"
	doxygen

install: all
	@echo "  INSTALL $(ARCHIVE)"
	$(_V)$(MKDIR) -p $(WF_TARGET_DIR)/wwcl/lib
	$(_V)$(CP) -ar include $(WF_TARGET_DIR)/wwcl/include
	$(_V)$(CP) -ar $(ARCHIVE) $(WF_TARGET_DIR)/wwcl/lib

compile_commands.json: $(OBJS) | Makefile
	@echo "  MERGE   compile_commands.json"
	$(_V)$(WF)/bin/wf-compile-commands-merge $@ $(patsubst %.o,%.cc.json,$^)

# Rules
# -----

$(BUILDDIR)/%.s.o : %.s build/font_ank.dat build/font_sjis.dat
	@echo "  AS      $<"
	@$(MKDIR) -p $(@D)
	$(_V)$(CC) $(ASFLAGS) -MMD -MP -MJ $(patsubst %.o,%.cc.json,$@) -c -o $@ $<

$(BUILDDIR)/%.c.o : %.c
	@echo "  CC      $<"
	@$(MKDIR) -p $(@D)
	$(_V)$(CC) $(CFLAGS) -MMD -MP -MJ $(patsubst %.o,%.cc.json,$@) -c -o $@ $<

build/font_ank.dat: $(ANK_FONT) tools/ank_font_pack.py
	@mkdir -p $(@D)
	$(PYTHON3) tools/ank_font_pack.py $(ANK_FONT) $@

build/font_sjis.dat: $(SJIS_FONT) tools/sjis_font_pack.py
	@mkdir -p $(@D)
	$(PYTHON3) tools/sjis_font_pack.py $(SJIS_FONT) $@


# Include dependency files if they exist
# --------------------------------------

-include $(DEPS)
