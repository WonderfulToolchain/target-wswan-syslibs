WONDERFUL_TOOLCHAIN ?= /opt/wonderful
include ../target/wswan/makedefs-common.mk

OBJDIR := build
SRCDIRS := src
MKDIRS := $(OBJDIR)

OBJECTS := \
	$(OBJDIR)/crt0_ws_bootfriend.o \
	$(OBJDIR)/crt0_ws_small.o \
	$(OBJDIR)/crt0_ws_medium.o \
	$(OBJDIR)/crt0_ww_asc1.o \
	$(OBJDIR)/crt0_ww_asc2.o \
	$(OBJDIR)/crt0_ww_jpn1.o \
	$(OBJDIR)/crt0_ww_jpn2.o
CFLAGS := $(WF_ARCH_CFLAGS)
ASFLAGS := -x assembler-with-cpp $(WF_ARCH_CFLAGS)
LDFLAGS := $(WF_ARCH_LDFLAGS)

DESTDIR ?= $(WF)

vpath %.c $(SRCDIRS)
vpath %.s $(SRCDIRS)

.PHONY: all clean install

all: $(OBJECTS)

$(OBJDIR)/crt0_ws_bootfriend.o: crt0_bootfriend.s $(OBJDIR)
	$(CC) $(ASFLAGS) -mcmodel=tiny -c -o $@ $<

$(OBJDIR)/crt0_ws_small.o: crt0.s $(OBJDIR)
	$(CC) $(ASFLAGS) -mcmodel=small -msegelf -c -o $@ $<

$(OBJDIR)/crt0_ws_medium.o: crt0.s $(OBJDIR)
	$(CC) $(ASFLAGS) -mcmodel=medium -msegelf -c -o $@ $<

$(OBJDIR)/crt0_ww_asc1.o: crt0_ww.s $(OBJDIR)
	$(CC) $(ASFLAGS) -mcmodel=small -msegelf -DDISPLAY_MODE_ASCII1 -c -o $@ $<

$(OBJDIR)/crt0_ww_asc2.o: crt0_ww.s $(OBJDIR)
	$(CC) $(ASFLAGS) -mcmodel=small -msegelf -DDISPLAY_MODE_ASCII2 -c -o $@ $<

$(OBJDIR)/crt0_ww_jpn1.o: crt0_ww.s $(OBJDIR)
	$(CC) $(ASFLAGS) -mcmodel=small -msegelf -DDISPLAY_MODE_JAPANESE1 -c -o $@ $<

$(OBJDIR)/crt0_ww_jpn2.o: crt0_ww.s $(OBJDIR)
	$(CC) $(ASFLAGS) -mcmodel=small -msegelf -DDISPLAY_MODE_JAPANESE2 -c -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(OBJECTS)

install: $(OBJECTS)
	install -d $(DESTDIR)/target/wswan/bootfriend/lib
	install -m 644 $(OBJDIR)/crt0_ws_bootfriend.o $(DESTDIR)/target/wswan/bootfriend/lib/crt0.o

	install -d $(DESTDIR)/target/wswan/small/lib
	install -m 644 $(OBJDIR)/crt0_ws_small.o $(DESTDIR)/target/wswan/small/lib/crt0.o

	install -d $(DESTDIR)/target/wswan/medium/lib
	install -m 644 $(OBJDIR)/crt0_ws_medium.o $(DESTDIR)/target/wswan/medium/lib/crt0.o

	install -d $(DESTDIR)/target/wwitch/lib
	install -m 644 $(OBJDIR)/crt0_ww_asc1.o $(DESTDIR)/target/wwitch/lib/crt0_asc1.o
	install -m 644 $(OBJDIR)/crt0_ww_asc2.o $(DESTDIR)/target/wwitch/lib/crt0_asc2.o
	install -m 644 $(OBJDIR)/crt0_ww_jpn1.o $(DESTDIR)/target/wwitch/lib/crt0_jpn1.o
	install -m 644 $(OBJDIR)/crt0_ww_jpn2.o $(DESTDIR)/target/wwitch/lib/crt0_jpn2.o
