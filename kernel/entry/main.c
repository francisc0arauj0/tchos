#include <cpu/gdt.h>
#include <cpu/sse.h>

void kmain()
{
    
    gdt_setup();
    sse_setup();

    for (;;)
    {
        asm volatile("hlt");
    }
}
