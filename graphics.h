#ifndef INCLUDE_GRAPHICS_H

#define INCLUDE_GRAPHICS_H
#include "utils.h"
#include "fonts.h"


void display_init();
void display_set_pixel(uint x, uint y, bool enabled);
bool display_get_pixel(uint x, uint y);
void display_clear();
void display_refresh();
void display_hardware_clear();

void graphics_draw_line(uvec2_t start, uvec2_t end);
void graphics_draw_char(uvec2_t pos, uint8_t c, font_t* font, bool level);
void graphics_draw_text(uvec2_t pos, char str[], font_t* font, bool level);

font_t* graphics_get_font(uint8_t height, bool bold, bool italic);


#endif /* INCLUDE_GRAPHICS_H */
