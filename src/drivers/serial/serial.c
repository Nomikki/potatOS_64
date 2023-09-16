#include <drivers/serial/serial.h>
#include <drivers/io/ports.h>

int init_serial()
{
    outportb(SERIAL_PORT + 1, 0x00);
    outportb(SERIAL_PORT + 3, 0x80);
    outportb(SERIAL_PORT + 0, 0x03);
    outportb(SERIAL_PORT + 1, 0x00);
    outportb(SERIAL_PORT + 3, 0x03);
    outportb(SERIAL_PORT + 2, 0xC7);
    outportb(SERIAL_PORT + 4, 0x0B);
    outportb(SERIAL_PORT + 4, 0x1E);
    outportb(SERIAL_PORT + 0, 0xAE);

    if (inportb(SERIAL_PORT + 0) != 0xAE)
    {
        return 1;
    }

    outportb(SERIAL_PORT + 4, 0x0F);

    return 0;
}

int serial_received()
{
    return inportb(SERIAL_PORT + 5) & 1;
}

char read_serial()
{
    while (serial_received() == 0)
        ;

    return inportb(SERIAL_PORT);
}

int is_transmit_empty()
{
    return inportb(SERIAL_PORT + 5) & 0x20;
}

void write_serial(char a)
{
    while (is_transmit_empty() == 0)
        ;

    outportb(SERIAL_PORT, a);
}