#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include <stdio.h>
#include "graphics.h"

int main() {
    display_init();
    display_hardware_clear();
    sleep_ms(1000);

    display_clear();
    display_refresh();

    for (int i = 0; i < 240; i++) {
        for (int j = 0; j < 400; j++) {
            display_set_pixel(j, i, (j + i) % 2);
        }
        display_refresh();
        sleep_ms(20);
    }

    display_clear();
    display_refresh();

    display_set_pixel(20, 20, 1);
    display_set_pixel(40, 40, 1);
    display_set_pixel(20, 40, 0);
    display_set_pixel(40, 20, 0);

    display_refresh();
    sleep_ms(200);

    for (int i = 0; i < 256; i++) {

        graphics_draw_char((uvec2_t) {(i / 16) * 15, (i % 16) * 15}, i, graphics_get_font(16, false, false), false);
        display_refresh();
        sleep_ms(100);
    }

    display_hardware_clear();
    sleep_ms(10);
    display_clear();
    display_refresh();
    sleep_ms(100);

    for (int i = 0; i < 256; i++) {
        graphics_draw_char((uvec2_t) {(i / 16) * 15, (i % 16) * 15}, i, graphics_get_font(12, false, false), false);
        display_refresh();
        sleep_ms(100);
    }

    while(true) {
        display_clear();

        display_refresh();

        sleep_ms(500);
        graphics_draw_text((uvec2_t) {0, 0}, "test 8/t/t", graphics_get_font(8, true, true), false);
        display_refresh();
        sleep_ms(500);
        graphics_draw_text((uvec2_t) {5, 20}, "test 12/t/t", graphics_get_font(12, true, true), false);
        display_refresh();
        sleep_ms(500);
        graphics_draw_text((uvec2_t) {10, 40}, "test 16/t/t", graphics_get_font(16, true, true), false);
        display_refresh();
        sleep_ms(500);
        graphics_draw_text((uvec2_t) {15, 60}, "test 30/f/f", graphics_get_font(30, false, false), false);
        display_refresh();
        sleep_ms(500);
        graphics_draw_text((uvec2_t) {20, 90}, "test 30/t/t", graphics_get_font(30, true, true), false);
        display_refresh();
        sleep_ms(500);
        graphics_draw_text((uvec2_t) {25, 130}, "test 42/f/f", graphics_get_font(42, false, false), false);
        display_refresh();
        sleep_ms(500);
        graphics_draw_text((uvec2_t) {30, 180}, "test 52/t/f", graphics_get_font(52, true, false), false);
        display_refresh();

        //display_set_pixel(4, 4, true);
        display_refresh();
        sleep_ms(4000);
    }
}
