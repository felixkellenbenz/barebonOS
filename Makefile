CC=i686-elf-gcc
AS=i686-elf-as


ifeq (, $(shell which $(CC) 2> /dev/null))
$(error "No i686-elf-gcc in PATH")
endif

ifeq (, $(shell which $(AS) 2> /dev/null))
$(error "No i686-elf-as in PATH")
endif

C_COMPILE_FLAGS=-g -std=gnu99 -ffreestanding -O2 -Wall -Wextra
C_LINK_FLAGS=-T linker.ld -ffreestanding -O2 -nostdlib -lgcc

SRCDIR=.

C_FILES = $(foreach D, $(SRCDIR), $(wildcard $(D)/*.c))
S_FILES = $(foreach D, $(SRCDIR), $(wildcard $(D)/*.s))

C_OBJFILES = $(patsubst %.c, %.c.o, $(C_FILES))
S_OBJFILES = $(patsubst %.s, %.s.o, $(S_FILES))

BINARY = bare_bones.bin

all: $(BINARY)
	$(info Discovered S sources: $(S_FILES))
	$(info Discovered C sources: $(C_FILES))

$(BINARY): $(C_OBJFILES) $(S_OBJFILES)
	$(CC) $(C_LINK_FLAGS) $(S_OBJFILES) $(C_OBJFILES) -o $(BINARY)

%.c.o: %.c
	$(CC) $(C_COMPILE_FLAGS) -c $^ -o $@ 

%.s.o: %.s
	$(AS) $^ -o $@

clean:
	$(info Removing $(C_OBJFILES) $(S_OBJFILES))
	@rm $(C_OBJFILES) $(S_OBJFILES) $(BINARY)
