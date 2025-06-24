CC=i686-elf-gcc

BUILD_DIR=./build/
LINK_FILE=./linker.ld
ISODIR=./isodir/
SUB_DIRS=./boot/ ./kernel/

OPTIMIZATION=-O2

LINK_FLAGS=-T $(LINK_FILE) -ffreestanding $(OPTIMIZATION) -nostdlib -lgcc

OS_NAME = barebonOS
BINARY = $(OS_NAME).bin
ISONAME = $(OS_NAME).iso

# How does this work ?
rwildcard = $(foreach d, $(wildcard $(1:=/*)), $(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d)) 

.PHONY: all clean iso write_grub_cfg create_isodir make_subdirs
all: $(BINARY)

$(BINARY): make_subdirs
	$(CC) $(LINK_FLAGS) $(patsubst ./build/%, ./build%, $(call rwildcard, $(BUILD_DIR), *.o)) -o $(BINARY)

clean:
	rm -f $(BINARY) 2> /dev/null
	rm -rf $(BUILD_DIR) 2> /dev/null
	rm -rf $(ISODIR) 2> /dev/null
	rm -f $(ISONAME) 2> /dev/null

iso: $(BINARY) write_grub_cfg
	mv $(BINARY) $(ISODIR)boot/$(BINARY)
	grub2-mkrescue -o $(ISONAME) $(ISODIR) 2> /dev/null

write_grub_cfg: create_isodir
	printf "menuentry \"$(OS_NAME)\" {\n" > $(ISODIR)boot/grub/grub.cfg
	printf "\t multiboot2 /boot/$(BINARY)\n" >> $(ISODIR)boot/grub/grub.cfg
	printf "\t boot \n }" >> $(ISODIR)boot/grub/grub.cfg

create_isodir:
	mkdir -p $(ISODIR)boot/grub
	touch $(ISODIR)boot/grub/grub.cfg

make_subdirs:
	make -C ./kernel/
	make -C ./boot/

