#ifndef KERNEL_MEM_PMM_H_
#define KERNEL_MEM_PMM_H_

#include <klib/stdio.h>
#include <kernel/mem/bitmap.h>

void pmm_setup(unsigned long addr, uint32_t size);
void *pmm_alloc_frame();
void pmm_free_frame();

#endif // KERNEL_MEM_PMM_H_