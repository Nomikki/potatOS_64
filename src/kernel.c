#include <drivers/serial/serial.h>
#include <drivers/display/vga.h>
#include <utils/log.h>

void kernel_main()
{
    print_clear();
    print_set_color(COLOR_WHITE, COLOR_BLACK);
    print_str("64bit potato!!!");

    if (init_serial() == 0)
    {
        print_str("Serial port initialized");
    }
    else
    {
        print_str("Error with serial port. :(");
    }

    log("Serial!!!\n");
    log("Mahtavaa!\n");

    while (1)
        ;
}