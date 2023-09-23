#define DEBUG 1

#include <drivers/serial/serial.h>
#include <kernel/arch/x64/vga.h>
#include <kernel/arch/x64/idt.h>
#include <kernel/mem/pmm.h>
#include <utils/log.h>
#include <klib/stdio.h>
#include <multiboot.h>

#define _HIGHER_HALF_KERNEL_MEM_START 0xffffffff80000000
extern uint64_t _kernel_start;
extern uint64_t _kernel_physical_end;
extern uint64_t _kernel_end;
extern uint64_t _kern_virtual_offset;

extern uint64_t multiboot_framebuffer_data;

extern uint64_t multiboot_basic_meminfo;
struct multiboot_tag_basic_meminfo *tagmem = NULL;
struct multiboot_tag_framebuffer *tagfb = NULL;
extern uint64_t p4_table[];
extern uint64_t end_of_mapped_memory;

uint64_t memory_size_in_bytes = 0;

void init_basic_system(unsigned long addr)
{
    struct multiboot_tag *tag;
    uint32_t mbi_size = *(uint32_t *)(addr + _HIGHER_HALF_KERNEL_MEM_START);

    tagmem = (struct multiboot_tag_basic_meminfo *)(multiboot_basic_meminfo + _HIGHER_HALF_KERNEL_MEM_START);
    tagfb = (struct multiboot_tag_framebuffer *)(multiboot_framebuffer_data + _HIGHER_HALF_KERNEL_MEM_START);

    memory_size_in_bytes = (tagmem->mem_upper + 1024) * 1024;

    klog("Mem: %u MB (%u KB)\n", memory_size_in_bytes / 1024 / 1024, memory_size_in_bytes / 1024);

    klog("Frame buffer info: type: 0x%X, address: 0x%Z\n", tagfb->common.framebuffer_type, tagfb->common.framebuffer_addr);
    klog("width: %u, height: %u, bpp: %u, pitch: %u\n", tagfb->common.framebuffer_width, tagfb->common.framebuffer_height, tagfb->common.framebuffer_bpp, tagfb->common.framebuffer_pitch);

    klog("End of mapped mem: 0x%Z\n", end_of_mapped_memory);

    pmm_setup(addr, mbi_size);

    klog("mapped tables:\n");
    for (int i = 0; i < 512; i++)
    {
        if (p4_table[i] != 0)
            klog("%i: 0x%Z\n", i, (uint64_t)p4_table[i]);
    }
}

void kernel_start(unsigned long addr, unsigned long magic)
{
    print_clear();
    print_set_color(COLOR_LIGHT_GRAY, COLOR_BLACK);

    init_serial();

    klog("PotatOS\n");

    init_basic_system(addr);

    uint64_t kernelStart = (uint64_t)&_kernel_start;
    uint64_t kernelEnd = (uint64_t)&_kernel_physical_end;
    uint64_t kernelSize = (((unsigned long)&_kernel_end + (1024 * 1024)) - (unsigned long)&_kern_virtual_offset);

    klog("virtual offset: %Z\n", (unsigned long)&_kern_virtual_offset);

    unsigned size = *(unsigned *)(addr + _HIGHER_HALF_KERNEL_MEM_START);

    if (magic == 0x36d76289)
    {
        klog("Magic number verified Size:  %X - Magic: %X\n", size, magic);
    }
    else
    {
        klog("Failed to verify magic number. Something is wrong\n");
    }

    setup_idt();

    while (1)
        ;
}