#include <kernel/mem/bitmap.h>
#include <stdint.h>
#include <multiboot.h>

uint32_t used_frames;
uint64_t memory_map_phys_addr;
uint32_t bitmap_size;

extern struct multiboot_tag_basic_meminfo *tagmem;

void bitmap_init(unsigned long end_of_reserved_area)
{
    used_frames = 0;
    uint64_t memory_size = (tagmem->mem_upper + 1024) * 1024;
    bitmap_size = memory_size / 0x1000l + 1;
}

void bitmap_get_region(uint64_t *base_address, size_t *length_in_bytes)
{
    *base_address = (uint64_t)memory_map_phys_addr;
    *length_in_bytes = bitmap_size / 8 + 1;
}