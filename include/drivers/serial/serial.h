#ifndef DRIVERS_IO_SERIAL_SERIAL_H
#define DRIVERS_IO_SERIAL_SERIAL_H

#define SERIAL_PORT 0x3f8

extern int serial_init();
extern int serial_received();
extern char read_serial();
extern int is_transmit_empty();
extern void serial_write(char a);

#endif // DRIVERS_IO_SERIAL_SERIAL_H