#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/sse.h>

void kmain()
{
    
    gdt_setup();
    idt_setup();
    sse_setup();

    for (;;)
    {
        asm volatile("hlt");
    }
}
