import os

d = os.listdir(".")

"""
font_t font_bold_12x30;
font_bold_12x30.height = 30;
font_bold_12x30.width = 12;
font_bold_12x30.font = bold_12x30;
"""

for f in d:
    try:
        size = f.split("_")[-1].split(".")[0]
        width, height = [int(i) for i in size.split("x")]
        filename = f.split(".")[0]
        font_file = "font_"+filename

        print("font_t "+font_file+" = {"+f"&{(filename)}[0], {width}, {height}"+"};")
        print()
    except:
        pass
