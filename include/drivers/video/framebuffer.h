#ifndef DRIVERS_VIDEO_FRAMEBUFFER_H_
#define DRIVERS_VIDEO_FRAMEBUFFER_H_

#include <stdint.h>

void framebuffer_init(unsigned long addr);
void plot_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
void draw_text(uint32_t cx, uint32_t cy, uint8_t r, uint8_t g, uint8_t b, const char *text);
void draw_testCanvas();
void framebuffer_flip();
void framebuffer_clear(uint8_t r, uint8_t g, uint8_t b);
void framebuffer_clear_black();


#endif // DRIVERS_VIDEO_FRAMEBUFFER_H_