#include <memory/memory.h>

void *memset(void *s, int c, u64 n)
{
    u8 *p = (u8 *)s;

    for (u64 i = 0; i < n; i++)
    {
        p[i] = (u8)c;
    }

    return s;
}

void *memcpy(void *restrict d, void *restrict s, u64 n)
{
    u8 *restrict pd = (u8 *restrict)d;
    const u8 *restrict ps = (const u8 *restrict);

    for (u64 i = 0; i < n; i++)
    {
        pd[i] = ps[i];
    }

    return d;
}
