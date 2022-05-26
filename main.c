#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include <stdio.h>
#include "graphics.h"
#include "keyboard.h"

int main() {
    display_init();
    display_hardware_clear();
    sleep_ms(200);

    display_clear();
    display_refresh();
    keyboard_init();
    sleep_ms(100);

    for (int i = 0; i < 16; i++) {
        graphics_draw_char((uvec2_t) {(i / 16) * 15, (i % 16) * 15}, i, graphics_get_font(16, false, false), false);
        display_refresh();
        sleep_ms(100);
    }

    display_clear();

    int i = 0;
    int max_cols = 320 / 16;

    while(true) {
        keyboard_refresh();

        if (keyboard_available()) {
            keypress_t kp = keyboard_pop();
            if (!kp.released) {
                int col = i % max_cols;
                int row = (i / max_cols) % 15;
                graphics_draw_char((uvec2_t) {col * 16, row * 16}, kp.keycode, graphics_get_font(16, false, false), false);
                i ++;
            }
        }

        graphics_draw_char((uvec2_t) {340, 40}, '0' + keyboard_pointer(), graphics_get_font(16, false, false), false);
        display_refresh();

        sleep_ms(10);
    }
}
