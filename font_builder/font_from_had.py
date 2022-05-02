import os
import numpy as np
import matplotlib.pyplot as plt
import math
from PIL import Image

headers = os.listdir("./had_fonts/")

for header in headers:
    print(header)
    f = open("./had_fonts/"+header, "r+")
    g = f.readlines()
    f.close()

    width, height = [int(i) for i in header.split(".")[0].split("x")]

    for i in range(len(g)):
        g[i] = g[i].split("//")[0].strip().replace("{", "[").replace("}","]").replace(";", "")
    data = np.array(eval("".join(g).split("=")[1]))

    font_chars = []
    for c, char in enumerate(data):
        if c > 0xff:
            continue
        char_data = []
        bytes_per_col = math.ceil(len(char) / height)
        # print(char, bytes_per_col)
        for i in range(0, len(char), bytes_per_col):
            # for each col:
            numerical = 0
            for j in range(bytes_per_col):
                # for each byte in col:
                numerical |= char[i+bytes_per_col-1-j]
                numerical <<= 8
            numerical >>= 8
            # print(bin(numerical), len(bin(numerical))-2, numerical)
            bits = []
            for k in range(bytes_per_col * 8):
                bits.append(numerical & 1)
                numerical >>= 1
            bits = bits[-height:]
            char_data.append(bits)
            # print(bits)

        char_data = np.array(char_data)
        char_data = np.rot90(char_data, k=3)
        char_data = np.fliplr(char_data)
        plt.subplot(16, 16, c+1)
        plt.imshow(char_data)

        font_chars.append(char_data)
    plt.show()

    i = 0
    font_widths = [width]
    font_heights = [height]
    font = "regular"

    # output
    font = font.split('.')[0]
    f = open(f"./out/{font.replace('-', '_')}_{font_widths[i]}x{font_heights[i]}.h", 'w+');
    byte_width = math.ceil((font_widths[i]) / 8)
    f.write(f"/* {font}-{font_widths[i]}x{font_heights[i]}, shape=(258, {font_heights[i]}, {byte_width}) */\n")
    f.write(f"#ifndef {font.replace('-', '_').upper()}_{font_widths[i]}X{font_heights[i]}_H\n")
    f.write(f"#define {font.replace('-', '_').upper()}_{font_widths[i]}X{font_heights[i]}_H\n")

    f.write(f"const uint8_t {font.replace('-', '_')}_{font_widths[i]}x{font_heights[i]}[258][{font_heights[i]}][{byte_width}] = ")
    f.write("{\n")

    for k in range(256):
        f.write("\t{");
        f.write(f" /* {format(k, '#004x')} = {chr(k) if chr(k).isprintable() else ' '} */")
        m = font_chars[k]
        for row in m:
            f.write("\n\t\t{");
            binint = 0
            for item in range(len(row)):
                binint |= row[-(item+1)]
                binint <<= 1
            byte_arr = []
            for byte in range(byte_width):
                b = binint & 0xFF
                byte_arr.append(b)
                binint >>= 8
            for byte in reversed(byte_arr):
                f.write(format(byte, '#004x'))
                f.write(",")

            f.write("},")
        f.write("\n\t},\n")

    f.write("\t{\n")
    # ending thing, font[256][0] is width, font[257][0] is height
    f.write("\t\t{")
    f.write(f"{format(font_widths[i] + 1, '#004x')},")
    for w in range(byte_width - 1):
        f.write("0x00,")
    f.write("}\n")

    f.write("\t\t{")
    f.write(f"{format(font_heights[i], '#004x')},")
    for w in range(byte_width - 1):
        f.write("0x00,")
    f.write("}\n")


    for y in range(font_heights[i] - 2):
        f.write("\t\t{")
        for w in range(byte_width):
            f.write("0x00,")
        f.write("}\n")

    f.write("\t}\n")

    f.write("}\n")
    f.write("#endif\n")

    f.close()

    # input()
    print("done")
