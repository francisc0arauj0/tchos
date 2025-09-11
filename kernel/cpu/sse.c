#include <cpu/sse.h>

static void enable_fpu()
{
    asm volatile (
        "mov %%cr0, %%rax\n"
        "and $0xFFFB, %%ax\n"
        "or $0x2, %%eax\n"
        "mov %%rax, %%cr0\n"
        : : : "rax"
    );
}

static void enable_sse()
{
    asm volatile (
        "mov %%cr4, %%rax\n"
        "or $0x600, %%rax\n"
        "mov %%rax, %%cr4\n"
        : : : "rax"
    );
}

void sse_setup()
{
    enable_sse();
    enable_fpu();
}
