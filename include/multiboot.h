#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

// ================================================
// general stuff

#define MULTIBOOT2_MAGIC          0xE85250D6
#define MULTIBOOT2_END_TAG_TYPE   0

struct multiboot_tag {
  uint32_t type;
  uint32_t size;
};

struct multiboot_color {
  uint8_t red; 
  uint8_t green;
  uint8_t blue;
};

// =================================================
// framebuffer stuff

#define MULTIBOOT_FRAMEBUFFER_TAG_TYPE 8
#define MULTIBOOT_FRAMEBUFFER_PALETT 0
#define MULTIBOOT_FRAMEBUFFER_CONTROL 1
#define MULTIBOOT_FRAMEBUFFER_EGA 2

struct framebuffer_info_common {
  uint32_t tag_type;
  uint32_t tag_size;
  uint64_t fb_addr;
  uint32_t fb_pitch;
  uint32_t fb_width;
  uint32_t fb_height;
  uint8_t fb_bpp;
  uint8_t fb_type;
  uint8_t fb_reserved;
};

struct framebuffer_info {

  struct framebuffer_info_common common_info;

  union {
    struct {
      uint32_t framebuffer_pallett_size;
      struct multiboot_color framebuffer_pallet[];
    };
    struct {
      uint8_t framebuffer_red_field_pos;  
      uint8_t framebuffer_red_mask_size;
      uint8_t framebuffer_green_field_pos;  
      uint8_t framebuffer_green_mask_size;
      uint8_t framebuffer_blue_field_pos;  
      uint8_t framebuffer_blue_mask_size;
    };
  };

};

void setup_bootinfo_parsing(uint32_t magic, uint32_t addr);

struct framebuffer_info find_framebuffer();

#endif
