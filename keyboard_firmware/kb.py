# ### CIRCUITPYTHON 7.3.0 ### #

from board import *
import digitalio
import busio
import time
import alarm

rows = (A0, A1, A2, A3)
cols = (D6, D5, D4, D3, D2, D9, SCK, MISO, MOSI, D10)

NONE = 0x00

keymaps = (
    ( # default layer
        #0     1     2     3     4     5     6     7     8     9
        (0x27, '\t', 1002, 1001, NONE, NONE, 0x12, 0x13, 1003, 1004),
        ('q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p' ),
        ('a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  0x0D),
        ('z',  'x',  'c',  'v',  ' ',  ' ',  'b',  'n',  'm',  0x08)
    ),

    ( # shift layer
        #0     1     2     3     4     5     6     7     8     9
        (0x27, '\t', NONE, 1001, NONE, NONE, 0x12, 0x13, NONE, NONE),
        ('Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',  'O',  'P' ),
        ('A',  'S',  'D',  'F',  'G',  'H',  'J',  'K',  'L',  0x0D),
        ('Z',  'X',  'C',  'V',  ' ',  ' ',  'B',  'N',  'M',  0x08)
    ),

    ( # num layer
        #0     1     2     3     4     5     6     7     8     9
        (0x27, '\t', 1002, NONE, NONE, NONE, 0x12, 0x13, NONE, NONE),
        ('1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0' ),
        ('!',  '@',  '#',  '$',  '%',  '^',  '&',  '*',  '(',  ')' ),
        ('-',  '_',  '+',  '=',  ' ',  ' ',  ';',  ':',  '\'', '"' )
    ),

    ( # fn layer
        #0     1     2     3     4     5     6     7     8     9
        (0x27, '\t', NONE, NONE, NONE, NONE, 0x12, 0x13, 1003, NONE),
        ('[',  ']',  '{',  '}',  '?',  '/',  '`',  '~',  '\\', '|' ),
        (0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA),
        (0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4)
    ),

    ( # null layer
        #0     1     2     3     4     5     6     7     8     9
        (0x27, '\t', NONE, NONE, NONE, NONE, 0x12, 0x13, NONE, 1004),
        (0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE),
        (0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8),
        (0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD7)
    )
)

currently_pressed = set([])
current_layer = 0

uart = busio.UART(TX, RX, baudrate=38400)

def do_nothing(*args):
    pass

print = do_nothing

def parse_value(value, release=False):
    global current_layer, currently_pressed, uart

    if value < 1000 and release:
        uart.write(chr(0x20).encode('latin'))
        print("rel ")
    print(value)

    if type(value) == str:
        value = ord(value)


    if value >= 1000:
        if release:
            for tup in currently_pressed:
                parse_value(keymaps[current_layer][tup[0]][tup[1]], True)
            current_layer = 0
        else:
            current_layer = (value - 1000) % 5
        print('new current layer '+str(current_layer))
    elif value != NONE:
        value = value % 256
        uart.write(chr(value).encode('latin'))


def check_data(keymaps, col_dio, row_dio):
    global current_layer

    for j, col in enumerate(col_dio):
        col.value = True
        time.sleep(0.0001)
        for i, row in enumerate(row_dio):
            if row.value:
                if not (i, j) in currently_pressed:
                    currently_pressed.add((i, j))
                    parse_value(keymaps[current_layer][i][j])
            else:
                if (i, j) in currently_pressed:
                    currently_pressed.discard((i, j))
                    parse_value(keymaps[current_layer][i][j], True)

        time.sleep(0.0001)
        col.value = False

def main():
    col_dio = [digitalio.DigitalInOut(col) for col in cols]
    row_dio = [digitalio.DigitalInOut(row) for row in rows]

    for i in range(len(col_dio)):
        col_dio[i].direction = digitalio.Direction.OUTPUT
        col_dio[i].value = False

    for i in range(len(row_dio)):
        row_dio[i].direction = digitalio.Direction.INPUT
        row_dio[i].pull = digitalio.Pull.DOWN

    while True:
        check_data(keymaps, col_dio, row_dio)
        time.sleep(1/40)


if __name__ == "__main__":
    main()

