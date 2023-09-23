#ifndef KERNEL_MEM_BITMAP_H
#define KERNEL_MEM_BITMAP_H

#include <stddef.h>
#include <stdint.h>

void bitmap_init(unsigned long end_of_reserved_area);

#endif // KERNEL_MEM_BITMAP_H
