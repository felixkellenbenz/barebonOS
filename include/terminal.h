#ifndef TERM_H
#define TERM_H

#include <stddef.h>
#include <stdint.h>

struct rgb_color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct rgba_color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha; 
};

void terminal_init(void(*f)(uint16_t, uint32_t, uint32_t, uint32_t, uint32_t),
                   uint32_t fg, uint32_t bg, size_t width, size_t height);

void terminal_clear();

void terminal_putchar(char c);

void terminal_putchar_pretty(char c, uint32_t fg, uint32_t bg);

void terminal_writestring(const char* s, size_t len);

void terminal_writestring_pretty(const char* s, size_t len,
                                 uint32_t fg, uint32_t bg);


#endif
