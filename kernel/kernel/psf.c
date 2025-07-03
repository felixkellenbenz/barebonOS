#include <stdint.h>

#include "psf.h"
#include "multiboot.h"

extern uint8_t _binary_kernel_font_psf_psflat9_16_psf_start;

// This relies on using the multiboot2 standard
// TODO: Abstract from concrete frambuffer structure
//       All we need is:
//          - Width of screen in bytes (fb->pitch)
//          - Bytes (or bits) per pixel
//          - Address of the framebuffer
extern struct framebuffer_info_common fb_info;


static uint8_t* font_start = &_binary_kernel_font_psf_psflat9_16_psf_start;

#define PIXEL uint32_t

struct psf_font get_psf_info() {
  return *((struct psf_font*)&font_start);
}

// cx and cy should probably be size_t
void psf_putchar_at(uint16_t c, uint32_t cx, uint32_t cy, uint32_t fg, uint32_t bg) {

  struct psf_font* font = (struct psf_font*)font_start;
  uint8_t* glyphs_start = (uint8_t*)font_start + font->headersize;

  uint8_t* glyph = glyphs_start + 
                   (c > 0 && c < font->num_glyphs ? c : 0) * font->bytes_per_glyph;

  uint32_t offs = 
    (cy * font->heigth * fb_info.fb_pitch) +
    (cx * font->width * (fb_info.fb_bpp / 8));

  for (uint32_t y = 0; y < font->heigth; y++) {
    
    uint32_t mask = 1 << (font->width - 1);
    uint32_t line = offs;

    for (uint32_t x = 0; x < font->width; x++) { 
      uint8_t* addr = (uint8_t*)fb_info.fb_addr;
      addr += line;

      // Why cast to uint32* ?
      // In general: How can we iterate over bitmap ? 
      *((PIXEL*)addr) = *((uint32_t*)glyph) & mask ? fg : bg;

      mask >>= 1;

      // maybe round up in case fb_bpp is not divisible by 8
      line += (fb_info.fb_bpp + 7) / 8;
    }

    glyph += (font->width + 7) / 8;
    offs += fb_info.fb_pitch;
  }
}


