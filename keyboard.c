#include "keyboard.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"

#define KEYBOARD_STACK_SIZE         64
#define KEYBOARD_UART               uart0
#define KEYBOARD_BAUD               38400

#define KEYBOARD_RX                 1
#define KEYBOARD_TX                 0

keypress_t keyQueue[KEYBOARD_STACK_SIZE];

keypress_t* ptr = keyQueue;
keypress_t* read_ptr = keyQueue;
keypress_t* end = keyQueue + KEYBOARD_STACK_SIZE;

bool next_released = false;

void keyboard_init() {
    uart_init(KEYBOARD_UART, KEYBOARD_BAUD);
    gpio_set_function(KEYBOARD_TX, GPIO_FUNC_UART);
    gpio_set_function(KEYBOARD_RX, GPIO_FUNC_UART);
}

void keyboard_refresh() {
    if (uart_is_readable(KEYBOARD_UART)) {
        uint8_t c = uart_getc(KEYBOARD_UART);
        if (c == 0x10) {
            next_released = true;
            return;
        }
        keyboard_queue_append(c, next_released);
        if (next_released) next_released = false;
    }
}

void keyboard_queue_append(uint8_t c, bool released) {
    ptr->keycode = c;
    ptr->released = released;

    ptr ++;
    if (ptr >= end) ptr = keyQueue;
}

keypress_t keyboard_pop() {
    keypress_t kp = *(read_ptr);

    read_ptr ++;
    if (read_ptr >= end) read_ptr = keyQueue;

    return kp;
}

uint16_t keyboard_available() {
    return ptr - read_ptr;
}

uint16_t keyboard_pointer() {
    return ptr - keyQueue;
}
