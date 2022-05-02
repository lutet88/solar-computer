from PIL import ImageFont, ImageDraw, Image
import matplotlib.pyplot as plt
import os
import numpy as np
import math

font_heights = [30, 36, 42, 52, 64, 80, 120]
font_widths = [round(font_heights[i] * 0.36) for i in range(len(font_heights))]

print(font_heights)
print(font_widths)

input()

font_dir = "./fonts/"
fonts = os.listdir(font_dir)

for i in range(len(font_widths)):
    for font in fonts:
        font_chars = []
        for char in range(0, 256):

            im = Image.new('L', (48, 96));
            draw = ImageDraw.Draw(im)
            img_font = ImageFont.truetype(font_dir + font, size=80)
            draw.text((0, -4), chr(char), font=img_font, fill=(255))

            im = im.resize((font_widths[i], font_heights[i]))



            imarr = np.array(im)
            for row in range(font_heights[i]):
                for col in range(font_widths[i]):
                    imarr[row][col] = min(round(imarr[row][col] / 16) * 16, 255)
                    imarr[row][col] = 1 if imarr[row][col] > 0xFF * 0.78 else 0

            imarr = imarr.astype('bool')
            im = Image.fromarray(imarr, mode='L')
            # im = im.convert(mode='1')

            print(font_heights[i], font_widths[i], font_dir + font, char)
            plt.subplot(4, 16, (char % 64) + 1)
            plt.imshow(im)

            font_chars.append(np.array(im))
            #if (char + 1) % 64 == 0:
            #    # plt.get_current_fig_manager().full_screen_toggle()
            #    plt.show()

        # output
        font = font.split('.')[0]
        f = open(f"./out/{font.replace('-', '_')}_{font_widths[i]+1}x{font_heights[i]}.h", 'w+');
        byte_width = math.ceil((font_widths[i] + 1) / 8)
        f.write(f"/* {font}-{font_widths[i]+1}x{font_heights[i]}, shape=(258, {font_heights[i]}, {byte_width}) */\n")
        f.write(f"#ifndef {font.replace('-', '_').upper()}_{font_widths[i]+1}X{font_heights[i]}_H\n")
        f.write(f"#define {font.replace('-', '_').upper()}_{font_widths[i]+1}X{font_heights[i]}_H\n")

        f.write(f"const uint8_t {font.replace('-', '_')}_{font_widths[i]+1}x{font_heights[i]}[258][{font_heights[i]}][{byte_width}] = ")
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


