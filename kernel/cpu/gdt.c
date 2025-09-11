#include <cpu/gdt.h>


struct gdt_entry_struct gdt_entries[7];
struct gdt_ptr_struct gdt_ptr;

void gdt_setup()
{
    gdt_ptr.limit = sizeof(struct gdt_entry_struct) * 7 - 1;
    gdt_ptr.base = (u64)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0, 0x9A, 0xA0);
    gdt_set_gate(2, 0, 0, 0x92, 0xC0);

    gdt_load(&gdt_ptr);

    asm volatile (
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%ss\n"
        "pushq $0x08\n"
        "lea 1f(%%rip), %%rax\n"
        "pushq %%rax\n"
        "lretq\n"
        "1:\n"
        : : : "rax", "memory"
    );
}


void gdt_set_gate(u64 id, u64 base, u64 limit, u8 access, u8 flags)
{
    gdt_entries[id].base_low = base & 0xFFFF;
    gdt_entries[id].base_middle = (base >> 16) & 0xFF;
    gdt_entries[id].base_high = (base >> 24) & 0xFF;

    gdt_entries[id].limit = limit & 0xFFFF;
    gdt_entries[id].flags = (limit >> 16) & 0x0F;
    gdt_entries[id].flags |= flags & 0xF0;
    
    gdt_entries[id].access = access;

}

void gdt_load(const struct gdt_ptr_struct *gdt_ptr)
{
    asm volatile("lgdt %0" : : "m" (*gdt_ptr));
}

void gdt_store(struct gdt_ptr_struct *gdt_ptr)
{
    asm volatile("sgdt %0" : "=m" (*gdt_ptr));
}
