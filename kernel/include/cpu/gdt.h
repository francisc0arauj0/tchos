#ifndef GDT_H
#define GDT_H

#include <types.h>

struct gdt_entry_struct
{
    u16 limit;
    u16 base1;
    u8 base2;
    u8 access;
    u8 flags;
    u8 base3;
} __attribute__((packed));

struct gdt_ptr_struct
{
    u16 size;
    u64 offset;
} __attribute__ ((packed));

void gdt_setup();
void gdt_set_gate(u64 id, u64 base, u64 limit, u8 access, u8 flags);
void gdt_load(const struct gdt_ptr_struct *gdt_ptr);
void gdt_store(struct gdt_ptr_struct *gdt_ptr);

#endif
