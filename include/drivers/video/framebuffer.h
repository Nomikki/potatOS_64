#ifndef DRIVERS_VIDEO_FRAMEBUFFER_H_
#define DRIVERS_VIDEO_FRAMEBUFFER_H_

#include <stdint.h>

void framebuffer_init(unsigned long addr);
void plot_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);


#endif // DRIVERS_VIDEO_FRAMEBUFFER_H_