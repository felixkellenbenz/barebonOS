#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt/gdt.h"
#include "psf.h"
#include "multiboot.h"

#if defined(__linux__) 
#error "You are not using a cross compiler"
#endif

#if !defined(__i386__)
#error "No cross compiler"
#endif


// Locate Framebuffer
// Write to Framebuffer 
// How to use fonts ?
// Where to load gdt ?

struct framebuffer_info_common fb_info;

void kernel_main(uint32_t magic, uint32_t addr) {  
  
  setup_bootinfo_parsing(magic, addr);

  fb_info = find_framebuffer().common_info;

  gdt_init();

  
  


}
