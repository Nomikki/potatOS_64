
#include <drivers/display/vga.h>

const int NUM_COLS = 80;
const int NUM_ROWS = 25;

struct Char
{
    unsigned char ch;
    unsigned char col;
};

struct Char *buffer = (struct Char *)0xB8000;
int col = 0;
int row = 0;
unsigned char color = 7 | 0 << 4;

void clear_row(int row)
{
    struct Char empty = (struct Char){
        ' ',
        color,
    };

    for (int col = 0; col < NUM_COLS; col++)
    {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear()
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        clear_row(i);
    }
}

void print_newLine()
{
    col = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }

    for (int row = 1; row < NUM_ROWS; row++)
    {
        for (int col = 0; col < NUM_COLS; col++)
        {
            struct Char cha = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = cha;
        }
    }

    clear_row(NUM_ROWS - 1);
}

void print_char(char ch)
{
    if (ch == '\n')
    {
        print_newLine();
        return;
    }

    if (col > NUM_COLS)
    {
        print_newLine();
    }

    buffer[col + NUM_COLS * row] = (struct Char){(unsigned char)ch, color};
    col++;
}

void print_set_color(int fg, int bg)
{
    color = fg + (bg << 4);
}

void print_str(char *str)
{
    for (int i = 0; 1; i++)
    {
        char ch = (unsigned int)str[i];
        if (ch == '\0')
            return;

        print_char(ch);
    }
}
