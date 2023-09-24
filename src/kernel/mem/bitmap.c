#include <configs.h>
#include <kernel/mem/bitmap.h>
#include <stdint.h>
#include <multiboot.h>

extern struct multiboot_tag_basic_meminfo *tagmem;
extern uint64_t _kernel_end;
extern uint64_t _kern_virtual_offset;

uint32_t used_frames;
uint64_t memory_map_phys_addr;
uint32_t bitmap_size;
uint32_t number_of_entries = 0;
uint64_t *memory_map = (uint64_t *)&_kernel_end;

void bitmap_init(unsigned long end_of_reserved_area)
{
    used_frames = 0;
    uint64_t memory_size = (tagmem->mem_upper + 1024) * 1024;
    bitmap_size = memory_size / 0x1000l + 1;
    number_of_entries = bitmap_size / 64 + 1;

    memory_map = (uint64_t*)(memory_map_phys_addr + _HIGHER_HALF_KERNEL_MEM_START);

    for (int i = 0; i < number_of_entries; i++)
    {
        memory_map[i] = 0x0;
    }
}

void bitmap_get_region(uint64_t *base_address, size_t *length_in_bytes)
{
    *base_address = (uint64_t)memory_map_phys_addr;
    *length_in_bytes = bitmap_size / 8 + 1;
}