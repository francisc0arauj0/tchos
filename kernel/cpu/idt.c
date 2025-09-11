#include <cpu/idt.h>

struct interrupt_descriptor_struct interrupts[256];
struct idt_ptr_struct idt_ptr;

void idt_set_gate(struct interrupt_descriptor_struct *interrupt, u8 id, void *offset, u8 type)
{
   interrupt[id].offset1 = (u64)offset & 0xFFFF;
   interrupt[id].offset2 = ((u64)offset >> 16) & 0xFFFF;
   interrupt[id].offset3 = ((u64)offset >> 32) & 0xFFFFFFFF;

   interrupt[id].type = type | 0x80;
   interrupt[id].zero = 0;
   interrupt[id].selector = 0x08;
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


