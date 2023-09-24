#include <drivers/video/framebuffer.h>
#include <multiboot.h>
#include <utils/log.h>
#include <kernel/arch/x64/vga.h>
#include <klib/stdio.h>
#include <klib/string.h>

#define PSF1_FONT_MAGIC 0x0436

typedef struct
{
    uint16_t magic;        // Magic bytes for idnetiifcation.
    uint8_t fontMode;      // PSF font mode
    uint8_t characterSize; // PSF character size.
} PSF1_Header;

#define PSF_FONT_MAGIC 0x864ab572

typedef struct
{
    uint32_t magic;         /* magic bytes to identify PSF */
    uint32_t version;       /* zero */
    uint32_t headersize;    /* offset of bitmaps in file, 32 */
    uint32_t flags;         /* 0 if there's no unicode table */
    uint32_t numglyph;      /* number of glyphs */
    uint32_t bytesperglyph; /* size of each glyph */
    uint32_t height;        /* height in pixels */
    uint32_t width;         /* width in pixels */
} PSF_font;

PSF_font *font;

uint32_t *framebuffer = (uint32_t *)0xffffffffbd000000;

uint32_t framebuffer_buffer[800 * 600];

extern struct multiboot_tag_framebuffer *tagfb;
extern char _binary_font_psf_start;
int font_bytesPerLine;

void draw_text(uint32_t cx, uint32_t cy, uint8_t r, uint8_t g, uint8_t b, const char *text)
{
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        uint8_t ch = text[i];
        uint8_t *glyph = (uint8_t *)&_binary_font_psf_start + font->headersize + (ch > 0 && ch < font->numglyph ? ch : 0) * font->bytesperglyph;

        int mask;
        for (uint32_t y = 0; y < font->height; y++)
        {
            mask = 1 << (font->width - 1);
            for (uint32_t x = 0; x < font->width; x++)
            {
                if (*((unsigned int *)glyph) & mask)
                {
                    plot_pixel(cx + (i * font->width) + x, cy + font->height + y, r, g, b);
                }

                mask >>= 1;
            }

            glyph += font_bytesPerLine;
        }
    }
}

void draw_testCanvas()
{
    for (int y = 0; y < tagfb->common.framebuffer_height; y++)
    {
        for (int x = 0; x < tagfb->common.framebuffer_width; x++)
        {
            plot_pixel(x, y, x % 255, y % 255, 0);
        }
    }
}

void framebuffer_init(unsigned long addr)
{
    if (tagfb->common.type == 5)
    {
        font = (PSF_font *)&_binary_font_psf_start;
        font_bytesPerLine = (font->width + 7) / 8;

        // framebuffer = addr;
        klog("Frame buffer info: type: 0x%X, address: 0x%Z\n", tagfb->common.framebuffer_type, tagfb->common.framebuffer_addr);
        klog("width: %u, height: %u, bpp: %u, pitch: %u\n", tagfb->common.framebuffer_width, tagfb->common.framebuffer_height, tagfb->common.framebuffer_bpp, tagfb->common.framebuffer_pitch);

        klog("font bytes per line: %u\n", font_bytesPerLine);

        klog("font magic: %X\n", font->magic);
        klog("font size: %i * %i\n", font->width, font->height);
    }
}

void plot_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t row = y * tagfb->common.framebuffer_width;
    uint32_t column = x;

    framebuffer_buffer[column + row] = (r << 16) | (g << 8) | (b);
}

void framebuffer_clear(uint8_t r, uint8_t g, uint8_t b)
{
    uint64_t size = tagfb->common.framebuffer_width * tagfb->common.framebuffer_height;
    for (uint32_t i = 0; i < size; i += 2)
    {
        framebuffer_buffer[i] = 0;
        framebuffer_buffer[i + 1] = 0;
    }
}

void framebuffer_clear_black()
{
    framebuffer_clear(0, 0, 0);
}

void framebuffer_flip()
{
    for (uint32_t i = 0; i < tagfb->common.framebuffer_width * tagfb->common.framebuffer_height; i++)
    {
        framebuffer[i] = framebuffer_buffer[i];
    }
}