CC=i686-elf-gcc
AS=i686-elf-as

ifeq (, $(shell which $(CC) 2> /dev/null))
$(error "No i686-elf-gcc in PATH")
endif

ifeq (, $(shell which $(AS) 2> /dev/null))
$(error "No i686-elf-as in PATH")
endif

SRCDIR=./src
INCLUDEDIR=./include
BUILDDIR=./build
LNK_FILE=./src/linker.ld
ISODIR=./isodir

C_COMPILE_FLAGS=-g -std=gnu99 $(foreach D, $(INCLUDEDIR), -I$(D)) -ffreestanding -O2 -Wall -Wextra -MP -MD
C_LINK_FLAGS=-T $(LNK_FILE) -ffreestanding -O2 -nostdlib -lgcc

C_FILES = $(foreach D, $(SRCDIR), $(wildcard $(D)/*.c))
S_FILES = $(foreach D, $(SRCDIR), $(wildcard $(D)/*.s))

C_OBJFILES = $(patsubst %.c, $(BUILDDIR)/%.c.o, $(C_FILES))
S_OBJFILES = $(patsubst %.s, $(BUILDDIR)/%.s.o, $(S_FILES))

DEP_FILES = $(patsubst %.c, $(BUILDDIR)/%.c.d, $(C_FILES)) $(patsubst %.s, $(BUILDDIR)/%.s.d, $(S_FILES)) 

OS_NAME = bare_bones
BINARY = $(OS_NAME).bin
ISONAME = $(OS_NAME).iso

all: $(BINARY)

$(BINARY): $(C_OBJFILES) $(S_OBJFILES)
	$(CC) $(C_LINK_FLAGS) $(S_OBJFILES) $(C_OBJFILES) -o $(BINARY)

$(BUILDDIR)/%.c.o: %.c create_build_dir
	$(CC) $(C_COMPILE_FLAGS) -c $< -o $@ 

$(BUILDDIR)/%.s.o: %.s create_build_dir
	$(AS) $< -o $@

clean:
	$(info Removing: $(BINARY))
	@rm -f $(BINARY) 2> /dev/null
	$(info Removing: $(BUILDDIR))
	@rm -rf $(BUILDDIR) 2> /dev/null
	$(info Removing: $(ISODIR))
	@rm -rf $(ISODIR) 2> /dev/null
	$(info Removing: $(ISONAME))
	@rm -f $(ISONAME) 2> /dev/null

iso: $(BINARY) write_grub_cfg
	@mv $(BINARY) $(ISODIR)/boot/$(BINARY)
	@grub2-mkrescue -o $(ISONAME) $(ISODIR) 2> /dev/null

create_build_dir:
	@mkdir -p $(BUILDDIR)/$(SRCDIR)

write_grub_cfg: create_isodir
	@printf "menuentry \"$(OS_NAME)\" {\n" > $(ISODIR)/boot/grub/grub.cfg
	@printf "\t multiboot2 /boot/$(BINARY)\n" >> $(ISODIR)/boot/grub/grub.cfg
	@printf "\t boot \n }" >> $(ISODIR)/boot/grub/grub.cfg

create_isodir:
	@mkdir -p $(ISODIR)/boot/grub
	@touch $(ISODIR)/boot/grub/grub.cfg
