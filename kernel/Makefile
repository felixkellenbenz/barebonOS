CC=i686-elf-gcc
AS=i686-elf-as
OBJCOPY=i686-elf-objcopy

SRC_DIRS=./ ./gdt/ ./font/
INCLUDE_DIRS=./../include/
BUILD_DIR=./../build/

DEBUG=-g
OPTIMIZATION=-O2
CC_COMPILE_FLAGS=$(DEBUG) -std=gnu99 $(foreach D, $(INCLUDE_DIRS), -I$(D)) -ffreestanding $(OPTIMIZATION) -Wall -Wextra -MP -MD

PREFIX=./kernel/

C_FILES=$(foreach DIR, $(SRC_DIRS), $(wildcard $(DIR)*.c))
S_FILES=$(foreach DIR, $(SRC_DIRS), $(wildcard $(DIR)*.s))
PSF_FILES=$(foreach DIR, $(SRC_DIRS), $(wildcard $(DIR)*.psf))

C_OBJFILES=$(patsubst %.c, $(BUILD_DIR)$(PREFIX)%.c.o, $(C_FILES))
S_OBJFILES=$(patsubst %.s, $(BUILD_DIR)$(PREFIX)%.s.o, $(S_FILES))
PSF_OBJFILES=$(patsubst %.psf, $(BUILD_DIR)$(PREFIX)%.psf.o, $(PSF_FILES))

DEP_FILES = $(patsubst %.c, $(BUILDDIR)$(PREFIX)%.c.d, $(C_FILES)) $(patsubst %.s, $(BUILDDIR)$(PREFIX)%.s.d, $(S_FILES)) 

.PHONY: all create_build_dirs
all: $(C_OBJFILES) $(S_OBJFILES) $(PSF_OBJFILES)

$(BUILD_DIR)$(PREFIX)%.s.o: %.s create_build_dirs
	$(AS) -c $< -o $@

$(BUILD_DIR)$(PREFIX)%.c.o: %.c create_build_dirs
	$(CC) $(CC_COMPILE_FLAGS) -c $< -o $@ 

$(BUILD_DIR)$(PREFIX)%.psf.o: %.psf create_build_dirs
	$(OBJCOPY) -O elf32-i386 -B i386 -I binary $< $@

create_build_dirs:
	$(foreach DIR, $(SRC_DIRS), $(shell mkdir -p $(BUILD_DIR)$(PREFIX)$(DIR))) 

