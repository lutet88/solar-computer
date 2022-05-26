#include "utils.h"
#include "graphics.h"
#include "fonts.h"
#include "keyboard.h"
#include <stdlib.h>
#include "commands.h"

#define GREETING "welcome to solar computer v1.1!\7enter commands below:\n"

uint8_t* terminal;
uint8_t* terminal_end;
uvec2_t terminal_offset;
uvec2_t terminal_size;
font_t* terminal_font;

uint8_t* cursor;
uint8_t* execute_ptr;

void terminal_init(uvec2_t offset, uvec2_t size, font_t* font) {
    terminal_offset = offset;
    terminal_size = size;
    terminal_font = font;

    int cols = terminal_size.x / font->width;
    int rows = terminal_size.y / font->height;
    terminal = (uint8_t*) calloc(cols * rows, sizeof(uint8_t));
    terminal_end = terminal + cols * rows;
    cursor = terminal;
    execute_ptr = terminal;

    keyboard_init();

    terminal_greet();
}

void terminal_set_char(int col, int row, uint8_t value) {
    terminal[row * (terminal_size.x / terminal_font->width) + col] = value;
    graphics_draw_char(
            uvec2_add(terminal_offset, (uvec2_t) {col * terminal_font->width, row * terminal_font->height}),
            value,
            terminal_font,
            false
    );
}

void terminal_backspace() {
    cursor--;
    int offset = cursor - terminal;
    int cols = terminal_size.x / terminal_font->width;
    int rows = terminal_size.y / terminal_font->height;
    terminal_set_char(offset % cols, offset / cols, 0x00);
}

void terminal_newline() {
    int offset = cursor - terminal;
    int cols = terminal_size.x / terminal_font->width;
    int distance_from_next = cols - (offset % cols);
    cursor += distance_from_next;
}

void terminal_println(char str[]) {
    for (int i = 0; str[i] != '\0'; ++i) {
        terminal_add_char(str[i]);
    }
    terminal_exec_newline();
}

void terminal_exec_newline() {
    int offset = cursor - terminal;
    int cols = terminal_size.x / terminal_font->width;
    int distance_from_next = cols - (offset % cols);
    cursor += distance_from_next;

    execute_ptr = cursor;
}


void terminal_clear() {
    int cols = terminal_size.x / terminal_font->width;
    int rows = terminal_size.y / terminal_font->height;

    for (int i = 0; i < cols * rows; ++i) {
        terminal_set_char(i % cols, i / cols, 0x00);
    }

    cursor = terminal;
    execute_ptr = terminal;
}
void terminal_deinit() {
    free(terminal);
}

void terminal_execute() {
    int exec_offset = cursor - execute_ptr;
    if (exec_offset <= 0) return;
    char* str = malloc((exec_offset + 1) * sizeof(char));
    int i = 0;
    while (execute_ptr <= cursor) {
        str[i] = *execute_ptr;
        i ++;
        execute_ptr ++;
    }
    str[exec_offset] = '\0';

    // terminal_println(str);

    commands_execute(str);

    free(str);
}

void terminal_add_char(uint8_t value) {
    if (value == 0x08) { // backspace
        terminal_backspace();
        return;
    } else if (value == 0xAA || value == '\7') { // fn + enter
        terminal_newline();
        return;
    } else if (value == 0x0D || value == '\n') { // enter
        terminal_newline();
        terminal_execute();
        execute_ptr = cursor;
        return;
    } else if (value == 0xA9) { // clear
        terminal_clear();
        return;
    }


    int offset = cursor - terminal;
    int cols = terminal_size.x / terminal_font->width;
    int rows = terminal_size.y / terminal_font->height;
    terminal_set_char(offset % cols, offset / cols, value);
    cursor++;
}

void terminal_greet() {
    char greet[] = GREETING;
    for (int i = 0; i < sizeof(greet); ++i) {
        terminal_add_char(greet[i]);
    }
}

void terminal_refresh() {
    // 1. check for keyboard input
    uint8_t c;

    keyboard_refresh();
    if (keyboard_available()) {
        keypress_t kp = keyboard_pop();
        c = kp.keycode;
        if (!kp.released) {
            terminal_add_char(c);
        }
    }

    // 2. do anything else needed (none right now)
}
