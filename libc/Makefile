# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Adrian "asie" Siekierka, 2023

WONDERFUL_TOOLCHAIN ?= /opt/wonderful
TARGET ?= wswan/medium
WF_TARGET_DIR ?= $(WONDERFUL_TOOLCHAIN)/target/$(TARGET)
include $(WF_TARGET_DIR)/makedefs.mk

# Source code paths
# -----------------

INCLUDEDIRS	:= include
SOURCEDIRS	:= src

# Defines passed to all files
# ---------------------------

DEFINES		:=

# Libraries
# ---------

LIBDIRS		:= $(WF_TARGET_DIR)

# Build artifacts
# ---------------

NAME		:= c
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
		   -fno-jump-tables -g

ifeq ($(WF_TARGET),wwitch)
CFLAGS		+= -Os -DLIBC_LOCALE_SJIS
else
ifeq ($(WF_SUBTARGET),bootfriend)
CFLAGS		+= -Os -DLIBC_LOCALE_ASCII
else
CFLAGS		+= -O2 -DLIBC_LOCALE_ASCII
endif
endif

# Intermediate build files
# ------------------------

OBJS_SOURCES	:= $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(SOURCES_S))) \
		   $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(SOURCES_C)))

OBJS		:= $(OBJS_SOURCES)

DEPS		:= $(OBJS:.o=.d)

# Targets
# -------

.PHONY: all clean install

all: $(ARCHIVE)

$(ARCHIVE): $(OBJS)
	@echo "  AR      $@"
	@$(MKDIR) -p $(@D)
	$(_V)$(AR) rcs $@ $(OBJS)

clean:
	@echo "  CLEAN"
	$(_V)$(RM) $(ARCHIVE) $(BUILDDIR)

install: all
	@echo "  INSTALL $(ARCHIVE)"
# libww overrides some C headers.
ifeq ($(WF_TARGET),wwitch)
	$(_V)$(MKDIR) -p $(WF_TARGET_DIR)/libc/lib
	$(_V)$(CP) -ar include $(WF_TARGET_DIR)/libc
	$(_V)$(CP) -ar $(ARCHIVE) $(WF_TARGET_DIR)/libc/lib
else
	$(_V)$(MKDIR) -p $(WF_TARGET_DIR)/lib
	$(_V)$(CP) -ar include $(WF_TARGET_DIR)
	$(_V)$(CP) -ar $(ARCHIVE) $(WF_TARGET_DIR)/lib
endif

# Rules
# -----

$(BUILDDIR)/%.s.o : %.s
	@echo "  AS      $<"
	@$(MKDIR) -p $(@D)
	$(_V)$(CC) $(ASFLAGS) -MMD -MP -c -o $@ $<

$(BUILDDIR)/%.c.o : %.c
	@echo "  CC      $<"
	@$(MKDIR) -p $(@D)
	$(_V)$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

# Include dependency files if they exist
# --------------------------------------

-include $(DEPS)
