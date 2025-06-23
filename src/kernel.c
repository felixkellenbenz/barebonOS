#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"

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

void kernel_main(void) {

  gdt_init();



}
