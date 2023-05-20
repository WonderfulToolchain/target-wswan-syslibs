WF_TARGET := wswan
WF_SUBTARGET := medium

include $(dir $(lastword $(MAKEFILE_LIST)))../makedefs-common.mk

WF_ARCH_CFLAGS += -mcmodel=medium
WF_TARGET_DIR ?= $(WF)/target/wswan/medium
WF_CRT0 := $(WF_TARGET_DIR)/lib/crt0.o
