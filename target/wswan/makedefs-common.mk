WF := $(WONDERFUL_TOOLCHAIN)
CC := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-gcc
AR := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-ar
AS := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-as
LD := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-ld
NM := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-nm
OBJCOPY := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-objcopy
RANLIB := $(WF)/toolchain/gcc-ia16-elf/bin/ia16-elf-ranlib
ROMLINK := $(WF)/bin/wf-wswantool romlink
CP := cp
INSTALL := install
MKDIR := mkdir
RM := rm -rf

WF_ARCH_CFLAGS := -march=v30mz -mtune=v30mz -mregparmcall -msegelf -ffreestanding
WF_ARCH_ASFLAGS := --32-segelf
WF_ARCH_LDFLAGS :=
