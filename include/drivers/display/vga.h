#ifndef DRIVERS_DISPLAY_VGA_H
#define DRIVERS_DISPLAY_VGA_H

enum COLOR {
    COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GRAY = 7,
	COLOR_DARK_GRAY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_PINK = 13,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15,
};

extern void clear_row(int row);
extern void print_clear();
extern void print_newLine();
extern void print_char(char ch);
extern void print_set_color(int fg, int bg);
extern void print_str(char *str);

#endif // DRIVERS_DISPLAY_VGA_H