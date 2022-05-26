#include "commands.h"
#include "terminal.h"
#include "graphics.h"
#include "fonts.h"
#include <string.h>
#include "pico/stdlib.h"

char filepath[] = "/";

void commands_execute(char str[]) {
    if (strstr(str, "dir") != NULL) {
        commands_dir(filepath);
    } else if (strstr(str, "cd") != NULL) {
        commands_cd(str);
    } else if (strstr(str, "echo") != NULL) {
        commands_echo(str);
    } else if (strstr(str, "math") != NULL) {
        commands_math(str);
    } else if (strstr(str, "read") != NULL) {
        commands_read(str);
    } else if (strstr(str, "edit") != NULL) {
        commands_edit(str);
    } else if (strstr(str, "graphicstest") != NULL) {
        for (int i = 0; i < 256; i++) {
            graphics_draw_char((uvec2_t) {(i % 16) * 14, (i / 16) * 14}, i, graphics_get_font(12, false, false), false);
            display_refresh();
            sleep_ms(100);
        }
    } else {
        terminal_println("invalid command!");
    }
}

void commands_dir(char* path) {
    terminal_println("root directory /\7test.txt test_in.1 test_in.2\7test_out.1 test_out.2 audio.mp3");
}

void commands_cd(char* path) {
    // do nothing! :D
}

void commands_echo(char* echo) {
    terminal_println(echo + 4);
}

void commands_math(char* expression) {
    terminal_println("7");
}

void commands_read(char* path) {
    terminal_println("Hello, World!");
}

void commands_edit(char* path) {
    terminal_clear();
}
