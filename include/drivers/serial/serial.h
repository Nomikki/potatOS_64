#ifndef DRIVERS_IO_SERIAL_SERIAL_H
#define DRIVERS_IO_SERIAL_SERIAL_H

#define SERIAL_PORT 0x3f8

extern int init_serial();
extern int serial_received();
extern char read_serial();
extern int is_transmit_empty();
extern void write_serial(char a);

#endif // DRIVERS_IO_SERIAL_SERIAL_H