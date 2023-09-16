#include <drivers/serial/serial.h>
#include <drivers/display/vga.h>
#include <utils/log.h>
#include <klib/stdio.h>

void kernel_main()
{
    print_clear();
    print_set_color(COLOR_WHITE, COLOR_BLACK);
    
    init_serial();
    
    kprintf("64bit potato!!!");
    kprintf("Serial!!!\n");
    kprintf("Mahtavaa!\n");
    int a = 1337;
    kprintf("hex: %X -> %i", a, a);

    while (1)
        ;
}