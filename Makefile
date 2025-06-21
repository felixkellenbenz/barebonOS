CC=i686-elf-gcc
AS=i686-elf-as

ifeq (, $(shell which $(CC) 2> /dev/null))
$(error "No i686-elf-gcc in PATH")
endif

ifeq (, $(shell which $(AS) 2> /dev/null))
$(error "No i686-elf-as in PATH")
endif

SRCDIR=./src
BUILDDIR=./build
LNK_FILE=./src/linker.ld

C_COMPILE_FLAGS=-g -std=gnu99 -ffreestanding -O2 -Wall -Wextra
C_LINK_FLAGS=-T $(LNK_FILE) -ffreestanding -O2 -nostdlib -lgcc

C_FILES = $(foreach D, $(SRCDIR), $(wildcard $(D)/*.c))
S_FILES = $(foreach D, $(SRCDIR), $(wildcard $(D)/*.s))

C_OBJFILES = $(patsubst %.c, $(BUILDDIR)/%.c.o, $(C_FILES))
S_OBJFILES = $(patsubst %.s, $(BUILDDIR)/%.s.o, $(S_FILES))

BINARY = bare_bones.bin

all: $(BINARY)

$(BINARY): $(C_OBJFILES) $(S_OBJFILES)
	$(CC) $(C_LINK_FLAGS) $(S_OBJFILES) $(C_OBJFILES) -o $(BINARY)

$(BUILDDIR)/%.c.o: %.c create_build_dir
	$(CC) $(C_COMPILE_FLAGS) -c $< -o $@ 

$(BUILDDIR)/%.s.o: %.s create_build_dir
	$(AS) $< -o $@

clean:
	$(info Removing $(BUILDDIR))
	@rm -r $(BUILDDIR)

create_build_dir:
	@mkdir -p $(BUILDDIR)/$(SRCDIR)
