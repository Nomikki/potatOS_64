#include <kernel/mem/pmm.h>
#include <stdint.h>
#include <utils/log.h>

extern uint32_t used_frames;

void pmm_setup(unsigned long addr, uint32_t size)
{
    // klog("Addr: %Z, size: %X\n", addr, size);
    bitmap_init(addr + size);
    uint64_t bitmap_start_addr;
    size_t bitmap_size;
    bitmap_get_region(&bitmap_start_addr, &bitmap_size);
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