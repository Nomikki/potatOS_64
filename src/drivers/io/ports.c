#include <drivers/io/ports.h>

unsigned char inportb(int portnum)
{
    unsigned char data = 0;
    __asm__ __volatile__("inb %%dx, %%al"
                         : "=a"(data)
                         : "d"(portnum));
    return data;
}

void outportb(int portnum, unsigned char data)
{
    __asm__ __volatile__("outb %%al, %%dx" ::"a"(data), "d"(portnum));
}
