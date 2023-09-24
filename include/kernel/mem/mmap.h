#ifndef KERNEL_MEM_MMAP_H_
#define KERNEL_MEM_MMAP_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <multiboot.h>

void mmap_parse(struct multiboot_tag_mmap *mmap_root);
void mmap_setup();

uintptr_t mmap_determine_bitmap_region(uint64_t lower_limit, size_t bytes_needed);

#endif // KERNEL_MEM_MMAP_H_