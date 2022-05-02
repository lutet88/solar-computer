#ifndef INCLUDE_FONTS_H
#define INCLUDE_FONTS_H

typedef struct Font {
    uint8_t* font;
    uint8_t height;
    uint8_t width;
} font_t;

font_t graphics_get_font(uint8_t height, bool bold, bool italic);

#endif
