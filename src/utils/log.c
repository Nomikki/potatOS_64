#include <drivers/serial/serial.h>
#include <kernel/arch/x64/vga.h>

void log(char *str)
{
    for (int i = 0; 1; i++)
    {
        char ch = (unsigned int)str[i];
        if (ch == '\0')
            return;

        serial_write(ch);
        print_char(ch);
    }
}

extern char *getFileName(const char *path)
{
    const char *filename = path;
    const char *ptr = path;

    while (*ptr)
    {
        if (*ptr == '/' || *ptr == '\\')
        {
            filename = ptr + 1;
        }
        ptr++;
    }
    return (char *)filename;
}