#ifndef PSF_H
#define PSF_H

#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"

#define PSF_FONT_MAGIC    0x864ab572

struct psf_display_info {
  uint32_t pitch;
  uint8_t bytes_per_pixel;
  uint64_t fb_addr;
};

struct psf_font {
  uint32_t magic;
  uint32_t version;
  uint32_t headersize;
  uint32_t flags;
  uint32_t num_glyphs;
  uint32_t bytes_per_glyph;
  uint32_t heigth;
  uint32_t width;
};

// should add unicode translation table parsing -> need calloc
void psf_init(struct psf_display_info info);

void psf_putchar_at(uint16_t c, size_t cx, size_t cy, uint32_t fg, uint32_t bg);

inline struct psf_display_info multiboot2_to_display_info(struct framebuffer_info_common multiboot2_fb_info) {
  uint32_t bpp = (multiboot2_fb_info.fb_bpp + 7) / 8;
  struct psf_display_info info = {multiboot2_fb_info.fb_pitch, bpp, multiboot2_fb_info.fb_addr};
  return info;
}

uint32_t get_term_width_chars(uint32_t pixel_width);

uint32_t get_term_heigth_chars(uint32_t pixel_heigth);

struct psf_font get_psf_info();

#endif
