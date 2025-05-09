WF_TARGET := wwitch

include $(dir $(lastword $(MAKEFILE_LIST)))../wswan/makedefs-common.mk

WF_TARGET_DIR ?= $(WF)/target/wwitch

WF_LDSCRIPT := $(WF_TARGET_DIR)/link.ld
WF_CRT0_ASC1 := $(WF_TARGET_DIR)/lib/crt0_asc1.o
WF_CRT0_ASC2 := $(WF_TARGET_DIR)/lib/crt0_asc2.o
WF_CRT0_JPN1 := $(WF_TARGET_DIR)/lib/crt0_jpn1.o
WF_CRT0_JPN2 := $(WF_TARGET_DIR)/lib/crt0_jpn2.o

WF_ARCH_CFLAGS += -mcmodel=small -mno-callee-assume-ss-data-segment -msegelf -mno-segment-relocation-stuff
WF_ARCH_LDFLAGS += -L$(WF)/toolchain/gcc-ia16-elf/lib/v30mz-segelf-separate-stack/small
WF_ARCH_LIBDIRS += local/$(WF_TARGET_DIR) thirdparty/$(WF_TARGET_DIR) $(WF_TARGET_DIR) $(WF_TARGET_DIR)/libc

# Allow outputting Shift-JIS string literals.
WF_ARCH_CFLAGS += -fexec-charset=shift-jis
