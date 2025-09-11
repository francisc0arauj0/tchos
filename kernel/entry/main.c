#include <cpu/gdt.h>

void kmain()
{
    
    gdt_setup();

    for (;;)
    {
        asm volatile("hlt");
    }
}
