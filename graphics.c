#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include <stdio.h>
#include <string.h>
#include "graphics.h"
#include "utils.h"
#include "fonts.h"

#define DISPLAY_SPI spi1
#define DISPLAY_CS 29
#define DISPLAY_MOSI 27
#define DISPLAY_SCK 26
#define DISPLAY_MISO 28  // actually dummy but we need it for SPI to work

#define WIDTH 400
#define HEIGHT 240

/*** DISPLAY DRIVER ***/

#define BUF_SIZE (WIDTH * HEIGHT / 8)

#define BIT_WRITECMD 0x01
#define BIT_VCOM 0x02
#define BIT_CLEAR 0x04

uint8_t vcom = BIT_VCOM;
uint8_t buffer[BUF_SIZE];
bool changed[HEIGHT];

uint8_t reverse_bin(uint8_t num) {
    uint8_t rev = 0;
    for (uint i = 0; i < 8; ++i) {
        if (num & (1 << i)) rev |= 1 << (7 - i);
    }
    return rev;
}

void toggle_vcom() {
    vcom = vcom ? 0 : BIT_VCOM;
}

void display_init() {
    spi_init(DISPLAY_SPI, 2000000);
    spi_set_format(DISPLAY_SPI, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_LSB_FIRST);

    gpio_set_function(DISPLAY_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(DISPLAY_SCK, GPIO_FUNC_SPI);
    gpio_set_function(DISPLAY_MISO, GPIO_FUNC_SPI);

    gpio_set_pulls(DISPLAY_MOSI, 0, 0);
    gpio_set_pulls(DISPLAY_MISO, 0, 0);

    gpio_init(DISPLAY_CS);
    gpio_set_dir(DISPLAY_CS, GPIO_OUT);
    gpio_put(DISPLAY_CS, false);
    sleep_us(2); // thSCSL, just in case
    display_clear();
}

void display_set_pixel(int x, int y, bool enabled) {
    if (x >= WIDTH || y >= HEIGHT) return;
    uint index = y * WIDTH + x;
    if (enabled) {
        buffer[index / 8] |= (1 << (index % 8));
    } else {
        buffer[index / 8] &= ~(1 << (index % 8));
    }
    changed[y] = true;
}

bool display_get_pixel(int x, int y) {
    uint index = y * WIDTH + x;
    uint8_t val = buffer[index / 8];
    val >>= index % 8;
    val &= 0b1;
    return val ? true : false;
}


void display_clear() {
    for (int i = 0; i < BUF_SIZE; i++) {
        buffer[i] |= 0xFF;
    }
    for (int row = 0; row < HEIGHT; row++) {
        changed[row] = true;
    }
}

void display_hardware_clear() {
    uint8_t header = reverse_bin(BIT_CLEAR | vcom);
    uint8_t dummy = 0b00000000;
    gpio_put(DISPLAY_CS, true);
    sleep_us(6);
    spi_write_blocking(DISPLAY_SPI, &header, 1);
    spi_write_blocking(DISPLAY_SPI, &dummy, 1);
    sleep_us(2);
    gpio_put(DISPLAY_CS, false);
    sleep_us(2);
}

void display_refresh() {
    for (int i = 0; i < HEIGHT; i++) {
        if (changed[i]) {
            changed[i] = false;
            uint8_t* ptr = buffer + (i * WIDTH / 8);
            gpio_put(DISPLAY_CS, true);
            uint8_t header = reverse_bin(vcom | BIT_WRITECMD);
            uint8_t address = reverse_bin(i);
            uint8_t dummy[2];
            sleep_us(6); // tsSCS
            spi_write_blocking(DISPLAY_SPI, &header, 1);
            spi_write_blocking(DISPLAY_SPI, &address, 1);
            for (int j = 0; j < WIDTH / 8; ++j) {
                uint8_t temp = reverse_bin(ptr[j]);
                spi_write_blocking(DISPLAY_SPI, &temp, 1);
            }
            //spi_write_blocking(DISPLAY_SPI, ptr, WIDTH / 8);
            spi_write_blocking(DISPLAY_SPI, dummy, 2);
            sleep_us(2); // thSCS
            gpio_put(DISPLAY_CS, false);
            sleep_us(2); // thSCSL

        }
    }
    toggle_vcom();
}

/*** GRAPHICS DRIVER ***/

void graphics_draw_line(uvec2_t start, uvec2_t end){

}

void graphics_draw_char(uvec2_t pos, uint8_t c, font_t* font, bool level) {
    const uint8_t* bitmap = font->font + ((font->width + 7) / 8) * font->height * c;
    for (uint y = 0; y < font->height; ++y) {
        uint8_t temp = 0;
        for (uint x = 0; x < font->width + 1; ++x) {
            if (x % 8 == 0) temp = *(bitmap + y * ((font->width + 7) / 8) + (font->width / 8) - (x / 8));
            bool e = temp & 1;
            display_set_pixel(x + pos.x, y + pos.y, level == e);
            temp >>= 1;
        }
    }
}

void graphics_draw_text(uvec2_t pos, char str[], font_t* font, bool level) {
    uvec2_t temp = pos;
    for (uint i = 0; i < strlen(str); ++i) {
        graphics_draw_char(temp, str[i], font, level);
        temp.x += font->width;
    }
}

font_t* graphics_get_font(uint8_t height, bool bold, bool italic) {
    return fonts_get_font(height, bold, italic);
}
