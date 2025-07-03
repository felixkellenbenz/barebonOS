.intel_syntax noprefix
.global gdt_flush

gdt_flush:

  mov eax, [esp + 4]
  lgdt [eax]
 
  mov eax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:set_code_segment

set_code_segment:
  ret


.att_syntax prefix
