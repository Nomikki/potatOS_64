#ifndef KLIB_STDIO_H
#define KLIB_STDIO_H

#include <stddef.h>
#include <stdint.h>

#define NULL 0
#define EOF -1

extern int32_t kprintf(const char *format, ...);
extern int32_t putchar(int32_t character);
extern int32_t puts(const char *str);


#endif // KLIB_STDIO_H