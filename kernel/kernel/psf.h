#ifndef PSF_H
#define PSF_H

#include <stdint.h>

#define PSF_FONT_MAGIC    0x864ab572

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

// should add unicode translation table parsing
void psf_init();

struct psf_font get_psf_info();

void psf_putchar_at(uint16_t c, uint32_t cx, uint32_t cy, uint32_t fg, uint32_t bg);

#endif
