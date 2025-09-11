#include <cpu/idt.h>

struct interrupt_descriptor_struct interrupts[256];
struct idt_ptr_struct idt_ptr;

void idt_set_gate(u8 id, void *offset, u8 type)
{
   interrupts[id].offset1 = (u64)offset & 0xFFFF;
   interrupts[id].offset2 = ((u64)offset >> 16) & 0xFFFF;
   interrupts[id].offset3 = ((u64)offset >> 32) & 0xFFFFFFFF;

   interrupts[id].type = type | 0x80;
   interrupts[id].zero = 0;
   interrupts[id].selector = 0x08;
}

void idt_load(const struct idt_ptr_struct *idt_ptr)
{
    asm("lidt %0" : : "m" (*idt_ptr));
}

void idt_setup()
{
    idt_ptr.size = sizeof(struct interrupt_descriptor_struct) * 256 - 1;
    idt_ptr.offset = (u64)&interrupts;
    
    idt_load(&idt_ptr);
}


