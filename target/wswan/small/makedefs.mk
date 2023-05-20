WF_TARGET := wswan
WF_SUBTARGET := small

include $(dir $(lastword $(MAKEFILE_LIST)))../makedefs-common.mk

WF_ARCH_CFLAGS += -mcmodel=small
WF_ARCH_LDFLAGS += -L$(WF)/toolchain/gcc-ia16-elf/lib/v30mz/small
WF_TARGET_DIR ?= $(WF)/target/wswan/small
WF_CRT0 := $(WF_TARGET_DIR)/lib/crt0.o
