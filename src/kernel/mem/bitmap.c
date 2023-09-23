#include <kernel/mem/bitmap.h>
#include <stdint.h>

uint32_t used_frames;

void init_bitmap()
{
    used_frames = 0;
}