OBJDIR = ../lib
BUILDDIR = ../bin

OUTPUT = libc.a

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CPPSRC = $(call rwildcard,./,*.c)
OBJS = $(patsubst %.c, $(OBJDIR)/%_$(OUTPUT).o, $(CPPSRC))

TOOLCHAIN_BASE = /usr/local/foxos-x86_64_elf_gcc

CFLAGS = -mno-red-zone -ffreestanding -fpic -g -Iinclude -nostdinc
LDFLAGS = -r

ifeq (,$(wildcard $(TOOLCHAIN_BASE)/bin/foxos-gcc))
	CC = gcc
else
	CC = $(TOOLCHAIN_BASE)/bin/foxos-gcc
endif

ifeq (,$(wildcard $(TOOLCHAIN_BASE)/bin/foxos-nasm))
	ASM = nasm
else
	ASM = $(TOOLCHAIN_BASE)/bin/foxos-nasm
endif

ifeq (,$(wildcard $(TOOLCHAIN_BASE)/bin/foxos-gcc))
	LD = ld
else
	LD = $(TOOLCHAIN_BASE)/bin/foxos-ld
endif

ifeq (,$(wildcard $(TOOLCHAIN_BASE)/bin/foxos-ar))
	AR = ar
else
	AR = $(TOOLCHAIN_BASE)/bin/foxos-ar
endif

$(OUTPUT): $(OBJS)
	@echo LD $^
	@$(LD) $(LDFLAGS) -o $(BUILDDIR)/$@.o $^
	@echo AR $(BUILDDIR)/$@.o
	@$(AR) rcs $(BUILDDIR)/$@ $(BUILDDIR)/$@.o

$(OBJDIR)/%_$(OUTPUT).o: %.c
	@echo "CC $^ -> $@"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: build