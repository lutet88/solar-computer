#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Keypress {
    uint8_t keycode;
    bool released;
} keypress_t;

void keyboard_init();
void keyboard_refresh();
keypress_t keyboard_pop();
uint16_t keyboard_available();
uint16_t keyboard_pointer();
void keyboard_queue_append(uint8_t c, bool released);

#endif  /* INCLUDE_KEYBOARD_H */
