WF_TARGET := wswan
WF_SUBTARGET := bootfriend

include $(dir $(lastword $(MAKEFILE_LIST)))../makedefs-common.mk

WF_ARCH_CFLAGS += -mcmodel=tiny
WF_ARCH_LDFLAGS += -L$(WF)/toolchain/gcc-ia16-elf/lib/v30mz/tiny
WF_TARGET_DIR ?= $(WF)/target/wswan/bootfriend
WF_CRT0 := $(WF_TARGET_DIR)/lib/crt0.o
WF_LDSCRIPT := $(WF_TARGET_DIR)/link.ld
