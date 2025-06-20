#include <stddef.h>
#include <stdint.h>

#define GDT_SIZE 5

struct gdt_entry {

  uint32_t base;
  uint32_t limit;  
  uint8_t access_byte;
  uint8_t flags;

} __attribute__((packed));

struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

// probably better to make a struct that is exactly 8 bytes
// is more readable
uint64_t gdt[GDT_SIZE];
struct gdt_ptr gdt_info;

void encode_gdt_entry(uint8_t* target, struct gdt_entry entry) {

  if (entry.limit > 0xFFFFF) {
    return;
  }

  // limit
  target[0] = entry.limit & 0xFF;
  target[1] = (entry.limit >> 8) & 0xFF;
  target[6] = (entry.limit >> 16) & 0x0F;

  // base
  target[2] = entry.base & 0xFF;
  target[3] = (entry.base >> 8) & 0xFF;
  target[4] = (entry.base >> 16) & 0xFF;
  target[7] = (entry.base >> 24) & 0xFF;

  // access byte
  target[5] = entry.access_byte;
  
  // flags
  target[6] |= (entry.flags << 4);
}

void create_gdt_entry(uint32_t entry_num, 
                      uint32_t base,
                      uint32_t limit,
                      uint8_t access_byte,
                      uint8_t flags) { 
  struct gdt_entry entry = {base, limit, access_byte, flags};
  encode_gdt_entry((uint8_t*)(gdt + entry_num), entry);
}

void gdt_init(void) {

  create_gdt_entry(0, 0, 0, 0, 0);     

  create_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xC);     

  create_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xC);     

  create_gdt_entry(3, 0, 0xFFFFF, 0xFA, 0xA);     

  create_gdt_entry(4, 0, 0xFFFFF, 0xF2, 0xC);      

  // possibly task state segment (TSS)

  // is this cast safe ?
  gdt_info.limit = GDT_SIZE * sizeof(struct gdt_entry) - 1;
  gdt_info.base = (uint32_t)gdt;
}
