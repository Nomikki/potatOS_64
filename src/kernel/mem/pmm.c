#include <kernel/mem/pmm.h>
#include <stdint.h>
#include <klib/stdio.h>
#include <utils/log.h>

extern uint32_t used_frames;



void pmm_setup(unsigned long addr, uint32_t size)
{
    klog("addr: %Z, size: %X\n", addr, size);

    init_bitmap();
}

// allocate just one frame
void *pmm_alloc_frame()
{
    used_frames++;

    return NULL;
}

void pmm_free_frame()
{
    used_frames--;

    return NULL;
}