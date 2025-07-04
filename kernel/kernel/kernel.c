#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/terminal.h>

#include "psf.h"
#include "multiboot.h"

#if defined(__linux__) 
#error "You are not using a cross compiler"
#endif

#if !defined(__i386__)
#error "No cross compiler"
#endif

extern void gdt_init();
struct framebuffer_info_common fb_info;

size_t strlen(const char* s) {

  size_t len = 0;

  while (s[len])
    len++;

  return len;
}

// TODO: How can we support other bootloaders ?
void kernel_main(uint32_t magic, uint32_t addr) {  
  
  setup_bootinfo_parsing(magic, addr);

  // could this also be in terminal init ?
  struct framebuffer_info_common fb_info = find_framebuffer().common_info;
  psf_init(multiboot2_to_display_info(fb_info));
  terminal_init(psf_putchar_at, 0x00FFFFFF, 0,
                get_term_width_chars(fb_info.fb_width),
                get_term_heigth_chars(fb_info.fb_height));
  gdt_init();

  char* str = "AAAAAAAAAA";
  char* str1 = "root@bbOS";
  terminal_writestring_pretty(str1, strlen(str1), 0x0032CD32, 0);
  terminal_writestring("# ", 2);
  terminal_writestring(str, strlen(str));
}
