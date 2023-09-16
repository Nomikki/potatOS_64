#ifndef DRIVERS_IO_PORTS_H
#define DRIVERS_IO_PORTS_H

extern unsigned char inportb(int portnum);
extern void outportb(int portnum, unsigned char data);

#endif // DRIVERS_IO_PORTS_H