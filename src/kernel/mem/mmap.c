#include <configs.h>
#include <kernel/mem/mmap.h>
#include <klib/stdio.h>
#include <multiboot.h>
#include <utils/log.h>

uint32_t mmap_number_of_entries;
multiboot_memory_map_t *mmap_entries;


const char *mmap_types[] = {
    "Invalid",
    "Available",
    "Reserved",
    "Reclaimable",
    "NVS",
    "Defective"};

void mmap_parse(struct multiboot_tag_mmap *mmap_root)
{
    int total_entries = 0;
    mmap_number_of_entries = (mmap_root->size - sizeof(*mmap_root)) / mmap_root->entry_size;
    mmap_entries = (multiboot_memory_map_t *)mmap_root->entries;
#ifdef DEBUG
    for (int i = 0; i < mmap_number_of_entries; i++)
    {
        klog("%i: 0x%Z - len: 0x%Z - type: %i [%s]\n", i, mmap_entries[i].addr, mmap_entries[i].len, mmap_entries[i].type, mmap_types[mmap_entries[i].type]);
        total_entries++;
    }
    klog("Total entries: %i\n", total_entries);
#endif
}

void mmap_setup() {

}


uintptr_t mmap_determine_bitmap_region(uint64_t lower_limit, size_t bytes_needed)
{

    return NULL;
}