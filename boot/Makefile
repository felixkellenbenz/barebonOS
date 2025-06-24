CC=i686-elf-gcc
AS=i686-elf-as

SRC_DIRS=./
INCLUDE_DIRS=./../include/
BUILD_DIR=./../build/

OPTIMIZATION=-O2
CC_COMPILE_FLAGS=-std=gnu99 $(foreach D, $(INCLUDE_DIRS), -I$(D)) -ffreestanding $(OPTIMIZATION) -Wall -Wextra -MP -MD

PREFIX=./boot/

C_FILES=$(foreach DIR, $(SRC_DIRS), $(wildcard $(DIR)*.c))
S_FILES=$(foreach DIR, $(SRC_DIRS), $(wildcard $(DIR)*.s))

C_OBJFILES=$(patsubst %.c, $(BUILD_DIR)$(PREFIX)%.c.o, $(C_FILES))
S_OBJFILES=$(patsubst %.s, $(BUILD_DIR)$(PREFIX)%.s.o, $(S_FILES))

DEP_FILES = $(patsubst %.c, $(BUILDDIR)$(PREFIX)%.c.d, $(C_FILES)) $(patsubst %.s, $(BUILDDIR)$(PREFIX)%.s.d, $(S_FILES)) 

.PHONY: all create_build_dirs
all: $(C_OBJFILES) $(S_OBJFILES)
	$(info $(S_OBJFILES))

$(BUILD_DIR)$(PREFIX)%.s.o: %.s create_build_dirs
	$(AS) -c $< -o $@

$(BUILD_DIR)$(PREFIX)%.c.o: %.c create_build_dirs
	$(CC) $(CC_COMPILE_FLAGS) -c $< -o $@ 

create_build_dirs:
	$(foreach DIR, $(SRC_DIRS), $(shell mkdir -p $(BUILD_DIR)$(PREFIX)$(DIR))) 
