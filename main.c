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

    while(true) {
        display_clear();
        display_refresh();

        for (int i = 0; i < 240; i++) {
            for (int j = 0; j < 400; j++) {
                display_set_pixel(j, i, (j + i) % 2);
            }
            display_refresh();
            sleep_ms(20);
        }

        //display_set_pixel(4, 4, true);
        //display_refresh();
        sleep_ms(10);
    }
}
