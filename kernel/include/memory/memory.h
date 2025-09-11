#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

void *memset(void *s, int c, u64 n);
void *memcpy(void *restrict d, void *restrict s, u64 n);

#endif
