#include <stddef.h>
#include <stdint.h>

#include "psf.h"

#define PIXEL uint32_t

// This relies on using the multiboot2 standard
// TODO: Abstract from concrete frambuffer structure
//       All we need is:
//          - Width of screen in bytes (fb->pitch)
//          - Bytes (or bits) per pixel
//          - Address of the framebuffer


extern uint8_t _binary_kernel_font_psf_psflat9_16_psf_start;
static uint8_t* font_start = &_binary_kernel_font_psf_psflat9_16_psf_start;

struct psf_display_info display_info;

void psf_init(struct psf_display_info info) {
  display_info = info;
};

// cx and cy should probably be size_t
void psf_putchar_at(uint16_t c, size_t cx, size_t cy, uint32_t fg, uint32_t bg) {

  struct psf_font* font = (struct psf_font*)font_start;
  uint8_t* glyphs_start = (uint8_t*)font_start + font->headersize;

  uint8_t* glyph = glyphs_start + 
                   (c > 0 && c < font->num_glyphs ? c : 0) * font->bytes_per_glyph;

  uint32_t offs = 
    (cy * font->heigth * display_info.pitch) +
    (cx * font->width * display_info.bytes_per_pixel);

  for (uint32_t y = 0; y < font->heigth; y++) {
    
    uint32_t mask = 1 << (font->width - 1);
    uint32_t line = offs;

    for (uint32_t x = 0; x < font->width; x++) { 
      uint8_t* addr = (uint8_t*)display_info.fb_addr;
      addr += line;

      // Why cast to uint32* ?
      // In general: How can we iterate over bitmap ? 
      *((PIXEL*)addr) = *((uint32_t*)glyph) & mask ? fg : bg;

      mask >>= 1;

      line += display_info.bytes_per_pixel;
    }

    glyph += (font->width + 7) / 8;
    offs += display_info.pitch;
  }
}

struct psf_font get_psf_info() {
  return *((struct psf_font*)font_start);
}

inline uint32_t get_term_width_chars(uint32_t pixel_width) {
  struct psf_font font_info = *((struct psf_font*)font_start);
  return pixel_width / font_info.width;
}

inline uint32_t get_term_heigth_chars(uint32_t pixel_heigth) {
  struct psf_font font_info = *((struct psf_font*)font_start);
  return pixel_heigth / font_info.heigth;
}
