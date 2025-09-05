WF := $(WONDERFUL_TOOLCHAIN)
CC := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-gcc
AR := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-ar
AS := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-as
LD := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-ld
NM := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-nm
OBJCOPY := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-objcopy
RANLIB := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-ranlib
CP := cp
INSTALL := install
MKDIR := mkdir
RM := rm -rf

ifeq ($(WF_TARGET),wwitch)
MKFENT := $(WF)/bin/wf-wwitchtool mkfent
ROMUSAGE := $(WF)/bin/wf-wwitchtool usage
else
BUILDROM := $(WF)/bin/wf-wswantool build rom
BUILDGATE := $(WF)/bin/wf-wswantool build wgate
BUILDBFB := $(WF)/bin/wf-wswantool build bfb
ROMUSAGE := $(WF)/bin/wf-wswantool usage
endif

WF_ARCH_CFLAGS := -march=v30mz -mtune=v30mz -mregparmcall -ffreestanding
WF_ARCH_ASFLAGS := --32-segelf
WF_ARCH_LDFLAGS :=
WF_ARCH_LIBDIRS :=
