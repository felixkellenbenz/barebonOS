#include <stddef.h>
#include <stdint.h>

#include "gdt/gdt.h"

extern void gdt_flush(uint32_t gdt_info_addr);

#define GDT_SIZE 5

struct gdt_entry_unencoded {
  uint32_t base;
  uint32_t limit;
  uint8_t access_byte;
  uint8_t flags;
};

struct gdt_entry {
  uint16_t low_limit;
  uint16_t low_base;  
  uint8_t mid_base;
  uint8_t access_byte;
  uint8_t limit_and_flags;
  uint8_t high_base;
} __attribute__((packed));

struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[GDT_SIZE];
struct gdt_ptr gdt_info;

struct gdt_entry encode_gdt_entry(struct gdt_entry_unencoded raw_entry) { 

  struct gdt_entry entry;

  // limit
  entry.low_limit = raw_entry.limit & 0xFFFF;
  entry.limit_and_flags = (raw_entry.limit >> 16) & 0x0F;

  // base
  entry.low_base = raw_entry.base & 0xFFFF;
  entry.mid_base = (raw_entry.base >> 16) & 0xFF;
  entry.high_base = (raw_entry.base >> 24) & 0xFF;

  // access_byte
  entry.access_byte = raw_entry.access_byte;
  
  // flags
  entry.limit_and_flags |= (raw_entry.flags & 0x0F) << 4;

  return entry;
}

void create_gdt_entry(size_t entry_num,
                      uint32_t base,
                      uint32_t limit,
                      uint8_t access_byte,
                      uint8_t flags) {

  if (limit > 0xFFFFF) {
    return;
  }

  struct gdt_entry_unencoded raw_gdt_entry = {base, limit, access_byte, flags};

  gdt[entry_num] = encode_gdt_entry(raw_gdt_entry);
}

void gdt_init(void) {

  create_gdt_entry(0, 0, 0, 0, 0);     

  create_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xC);     

  create_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xC);     

  create_gdt_entry(3, 0, 0xFFFFF, 0xFA, 0xA);     

  create_gdt_entry(4, 0, 0xFFFFF, 0xF2, 0xC);      

  // possibly task state segment (TSS)

  gdt_info.limit = GDT_SIZE * sizeof(struct gdt_entry) - 1;
  gdt_info.base = (uint32_t)&gdt;

  gdt_flush((uint32_t)&gdt_info);
}
