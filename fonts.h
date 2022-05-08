#ifndef INCLUDE_FONTS_H
#define INCLUDE_FONTS_H
#include <stdbool.h>

typedef struct Font {
    const uint8_t* font;
    uint8_t width;
    uint8_t height;
} font_t;

font_t* fonts_get_font(uint8_t height, bool bold, bool italic);

#endif
