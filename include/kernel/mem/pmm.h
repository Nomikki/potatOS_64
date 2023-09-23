#ifndef KERNEL_MEM_PMM_H 
#define KERNEL_MEM_PMM_H 

#include <kernel/mem/bitmap.h>

void pmm_setup(unsigned long addr, uint32_t size);
void *pmm_alloc_frame();
void pmm_free_frame();

#endif // KERNEL_MEM_PMM_H
