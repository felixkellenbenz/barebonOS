#include <stddef.h>
#include <stdint.h>
#include <kernel/terminal.h>

// TODO: Add color abstraction

#define NEWLINE         '\n'
#define CARRIAGE_RETRUN '\r'
#define BACKSPACE       '\b'
#define HORIZONTAL_TAB  '\t'
#define FORM_FEED       '\f'

// we could also have a map the maps the terminal type (vga, frambuf, ...) to function pointers
static void (*scroll_one)(int8_t direction);
static void (*put_char_at)(uint16_t c, uint32_t cx, uint32_t cy, uint32_t fg, uint32_t bg);
static size_t terminal_width;
static size_t terminal_height;
static size_t terminal_x;
static size_t terminal_y;
static uint32_t terminal_bg;
static uint32_t terminal_fg;

static inline void handle_newline() {
  if (++terminal_y == terminal_height) {
    terminal_clear();
  }
  terminal_x = 0;
}

static inline void handle_carriage_return() {
  terminal_x = 0;
}

static inline void handle_backspace() {
  if (terminal_x > 0) {
    terminal_x--;
    terminal_putchar(' ');
  } else {
    terminal_y--;
    terminal_x = terminal_width - 1;
  }
}

static inline void handle_horizontal_tab() {
}

static inline void handle_form_feed() {
  terminal_clear();
}

void terminal_init(void (*f)(uint16_t, uint32_t, uint32_t, uint32_t, uint32_t),
                   uint32_t fg, uint32_t bg, size_t width, size_t height) {
  put_char_at = f;
  terminal_width = width;
  terminal_height = height;
  terminal_x = 0;
  terminal_y = 0;
  terminal_fg = fg;
  terminal_bg = bg;
  terminal_clear();
}

void terminal_putchar(char c) {

  switch (c) {
    case CARRIAGE_RETRUN:
      handle_carriage_return();   
      return;
    case NEWLINE:
      handle_newline();
      return;
    case BACKSPACE:
      handle_backspace();
      return;
    case HORIZONTAL_TAB:
      handle_horizontal_tab();
      return;
    case FORM_FEED:
      handle_form_feed();
      return;
    default:
      put_char_at(c, terminal_x, terminal_y, terminal_fg, terminal_bg);
      break;
  };

  if (++terminal_x == terminal_width) {
    terminal_x = 0;
    if (++terminal_y == terminal_height) {
      terminal_clear();
      terminal_y = 0;
    }
  }
}

void terminal_writestring_pretty(const char *s, size_t len, uint32_t fg, uint32_t bg) {
  for (size_t i = 0; i < len; i++) {
    terminal_putchar_pretty(s[i], fg, bg);
  }
}

void terminal_putchar_pretty(char c, uint32_t fg, uint32_t bg) {
  uint32_t cpy_term_color_fg = terminal_fg;
  uint32_t cpy_term_color_bg = terminal_bg;
  terminal_fg = fg;
  terminal_bg = bg;

  terminal_putchar(c);

  terminal_fg = cpy_term_color_fg;
  terminal_bg = cpy_term_color_bg;
}

void terminal_writestring(const char* s, size_t len) {
  for (size_t i = 0; i < len; i++) {
    terminal_putchar(s[i]);
  }
}

void terminal_clear() {
  for (size_t y = 0; y < terminal_height; y++) {
    for (size_t x = 0; x < terminal_width; x++) {
      put_char_at(' ', x, y, terminal_fg, terminal_bg);
    }
  }
}


