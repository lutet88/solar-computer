#ifndef INCLUDE_TERMINAL_H
#define INCLUDE_TERMINAL_H

#include <stdbool.h>
#include <stdint.h>
#include "utils.h"
#include "fonts.h"

void terminal_init(uvec2_t offset, uvec2_t size, font_t* font);
void terminal_clear();
void terminal_deinit();
void terminal_execute();
void terminal_update();
void terminal_greet();
void terminal_exec_newline();
void terminal_println(char str[]);

#endif /* INCLUDE_TERMINAL_H */
