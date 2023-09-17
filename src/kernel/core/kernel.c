#include <drivers/serial/serial.h>
#include <kernel/arch/x64/vga.h>
#include <kernel/arch/x64/idt.h>
#include <utils/log.h>
#include <klib/stdio.h>


void kernel_start(unsigned long addr, unsigned long magic)
{

    
    print_clear();
    print_set_color(COLOR_LIGHT_GRAY, COLOR_BLACK);

    init_serial();

    kprintf("64bit potato!!!");
    kprintf("Serial!!!\n");
    kprintf("Mahtavaa!\n");
    int a = 1337;
    kprintf("hex: %X -> %i", a, a);

    setup_idt();
    



    while (1)
        ;
}