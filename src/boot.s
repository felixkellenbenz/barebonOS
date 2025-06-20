.set ALIGN,    1<<0             
.set MEMINFO,  1<<1              
.set FLAGS,    ALIGN | MEMINFO  
.set MAGIC,    0x1BADB002        
.set CHECKSUM, -(MAGIC + FLAGS) 

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

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
