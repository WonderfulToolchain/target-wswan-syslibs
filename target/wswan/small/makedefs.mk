WF_TARGET := wswan
WF_SUBTARGET := small

include $(dir $(lastword $(MAKEFILE_LIST)))../makedefs-common.mk

WF_TARGET_DIR ?= $(WF)/target/wswan/small
WF_ARCH_CFLAGS += -mcmodel=small -msegelf
WF_ARCH_LDFLAGS += -L$(WF)/toolchain/gcc-ia16-elf/lib/v30mz-segelf/small
WF_ARCH_LIBDIRS += local/$(WF_TARGET_DIR) thirdparty/$(WF_TARGET_DIR) $(WF_TARGET_DIR)
WF_CRT0 := $(WF_TARGET_DIR)/lib/crt0.o
WF_LDSCRIPT := $(WF_TARGET_DIR)/link.ld
