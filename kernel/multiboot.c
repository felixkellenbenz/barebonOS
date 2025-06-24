#include <stddef.h>


#include "boot/multiboot.h"

static uint32_t mbi_magic;
static uint32_t mbi_addr;

void setup_bootinfo_parsing(uint32_t magic, uint32_t addr) {
  mbi_magic = magic;
  mbi_addr = addr;
}

struct framebuffer_info find_framebuffer() {

  struct multiboot_tag* tag;  
  struct framebuffer_info framebuf_info;

  for (tag = (struct multiboot_tag*) (mbi_addr + 8);
       tag->type != MULTIBOOT2_END_TAG_TYPE;
       tag = (struct multiboot_tag*) ((uint8_t*) tag
                                     + ((tag->size + 7) & ~7))) {
 
    if (tag->type != MULTIBOOT_FRAMEBUFFER_TAG_TYPE) {
      continue;
    }

    struct framebuffer_info* frambuf_tag = 
      (struct framebuffer_info*) tag;
  
    framebuf_info = *frambuf_tag;

    switch(frambuf_tag->common_info.fb_type) {
      case MULTIBOOT_FRAMEBUFFER_CONTROL:

        break;
      case MULTIBOOT_FRAMEBUFFER_PALETT:

        break;
      case MULTIBOOT_FRAMEBUFFER_EGA:

        break;
      default:

        break;
    }
  }

  return framebuf_info;
}

