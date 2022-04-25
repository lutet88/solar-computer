#ifndef INCLUDE_GRAPHICS_H

#define INCLUDE_GRAPHICS_H

void display_init();
void display_set_pixel(uint x, uint y, bool enabled);
bool display_get_pixel(uint x, uint y);
void display_clear();
void display_refresh();
void display_hardware_clear();

#endif /* INCLUDE_GRAPHICS_H */
