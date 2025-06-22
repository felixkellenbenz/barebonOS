.set AARCH,    0
.set HEAD_LEN, multiboot_end - multiboot_start
.set MAGIC,    0xE85250D6     
.set CHECKSUM, -(MAGIC + AARCH + HEAD_LEN) 


.section .multiboot
.align 8   // multiboot header so 8 Byte alignment
multiboot_start:
.long MAGIC
.long AARCH
.long HEAD_LEN
.long CHECKSUM

.align 8    // this is a tag so 8 Byte alignment
framebuffer_tag_start:
.short 5    // tag type 5 = framebuffer
.short 1    // flag so that the bootloader does not ignore this tag
.long framebuffer_tag_end - framebuffer_tag_start
.long 1024  // width of the frambuffer
.long 768   // height of the framebuffer
.long 32    // depth i.e how many bytes per pixel
framebuffer_tag_end:

.align 8    // this is a tag so 8 Byte alignment
.short 0    // each tags are terminated 
.short 0    // with a tag of type 0 and length 8
.long 8
multiboot_end:

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:

	mov $stack_top, %esp

  # load gdt, see gdt.c for gdt_init()
  call gdt_init
  lgdt [gdt_info]

  # populate segment registers
  mov $0x10, %eax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs 
  mov %ax, %gs
  mov %ax, %ss
  jmp $0x08, $set_code_segment

set_code_segment:

	call kernel_main

	cli
1:	
  hlt
	jmp 1b

.size _start, . - _start
