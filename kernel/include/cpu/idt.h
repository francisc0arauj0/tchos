#ifndef IDT_H
#define GDT_H

#include <types.h>

struct interrupt_descriptor_struct
{
    u16 offset1;
    u16 selector;
    u8 ist;
    u8 type;
    u16 offset2;
    u32 offset3;
    u32 zero;
} __attribute__((packed));

struct idt_ptr_struct
{
    u16 size;
    u64 offset;
} __attribute__((packed));

void idt_setup();
void idt_load(const struct idt_ptr_struct *idt_ptr);
void idt_set_gate(struct interrupt_descriptor_struct *interrupt, u8 id, void *offset, u8 type);

#endif
