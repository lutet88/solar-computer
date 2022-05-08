#include "utils.h"
#include "fonts/bold_12x30.h"
#include "fonts/bold_14x36.h"
#include "fonts/bold_16x42.h"
#include "fonts/bold_20x52.h"
#include "fonts/bold_24x64.h"
#include "fonts/bold_30x80.h"
//#include "fonts/bold_44x120.h"
#include "fonts/bold_italic_12x30.h"
#include "fonts/bold_italic_14x36.h"
#include "fonts/bold_italic_16x42.h"
#include "fonts/bold_italic_20x52.h"
#include "fonts/bold_italic_24x64.h"
#include "fonts/bold_italic_30x80.h"
//#include "fonts/bold_italic_44x120.h"
#include "fonts/italic_12x30.h"
#include "fonts/italic_14x36.h"
#include "fonts/italic_16x42.h"
#include "fonts/italic_20x52.h"
#include "fonts/italic_24x64.h"
#include "fonts/italic_30x80.h"
//#include "fonts/italic_44x120.h"
#include "fonts/regular_12x30.h"
#include "fonts/regular_14x36.h"
#include "fonts/regular_16x42.h"
#include "fonts/regular_20x52.h"
#include "fonts/regular_24x64.h"
#include "fonts/regular_30x80.h"
//#include "fonts/regular_44x120.h"
#include "fonts/regular_4x6.h"
#include "fonts/regular_6x8.h"
#include "fonts/regular_8x12.h"
#include "fonts/regular_10x16.h"
#include "fonts.h"

font_t font_bold_12x30 = {bold_12x30[0][0], 12, 30};

font_t font_bold_14x36 = {bold_14x36[0][0], 14, 36};

font_t font_bold_16x42 = {bold_16x42[0][0], 16, 42};

font_t font_bold_20x52 = {bold_20x52[0][0], 20, 52};

font_t font_bold_24x64 = {bold_24x64[0][0], 24, 64};

font_t font_bold_30x80 = {bold_30x80[0][0], 30, 80};

//font_t font_bold_44x120 = {bold_44x120, 44, 120};

font_t font_bold_italic_12x30 = {bold_italic_12x30[0][0], 12, 30};

font_t font_bold_italic_14x36 = {bold_italic_14x36[0][0], 14, 36};

font_t font_bold_italic_16x42 = {bold_italic_16x42[0][0], 16, 42};

font_t font_bold_italic_20x52 = {bold_italic_20x52[0][0], 20, 52};

font_t font_bold_italic_24x64 = {bold_italic_24x64[0][0], 24, 64};

font_t font_bold_italic_30x80 = {bold_italic_30x80[0][0], 30, 80};

//font_t font_bold_italic_44x120 = {bold_italic_44x120, 44, 120};

font_t font_italic_12x30 = {italic_12x30[0][0], 12, 30};

font_t font_italic_14x36 = {italic_14x36[0][0], 14, 36};

font_t font_italic_16x42 = {italic_16x42[0][0], 16, 42};

font_t font_italic_20x52 = {italic_20x52[0][0], 20, 52};

font_t font_italic_24x64 = {italic_24x64[0][0], 24, 64};

font_t font_italic_30x80 = {italic_30x80[0][0], 30, 80};

//font_t font_italic_44x120 = {italic_44x120, 44, 120};

font_t font_regular_12x30 = {regular_12x30[0][0], 12, 30};

font_t font_regular_14x36 = {regular_14x36[0][0], 14, 36};

font_t font_regular_16x42 = {regular_16x42[0][0], 16, 42};

font_t font_regular_20x52 = {regular_20x52[0][0], 20, 52};

font_t font_regular_24x64 = {regular_24x64[0][0], 24, 64};

font_t font_regular_30x80 = {regular_30x80[0][0], 30, 80};

//font_t font_regular_44x120 = {regular_44x120, 44, 120};

font_t font_regular_4x6 = {regular_4x6[0][0], 4, 6};

font_t font_regular_6x8 = {regular_6x8[0][0], 6, 8};

font_t font_regular_8x12 = {regular_8x12[0][0], 8, 12};

font_t font_regular_10x16 = {regular_10x16[0][0], 10, 16};

font_t* fonts_get_font(uint8_t height, bool bold, bool italic) {
    if (bold && italic) {
        if (height < 7) return &font_regular_4x6;
        else if (height < 10) return &font_regular_6x8;
        else if (height < 14) return &font_regular_8x12;
        else if (height < 22) return &font_regular_10x16;
        else if (height < 33) return &font_bold_italic_12x30;
        else if (height < 39) return &font_bold_italic_14x36;
        else if (height < 47) return &font_bold_italic_16x42;
        else if (height < 58) return &font_bold_italic_20x52;
        else if (height < 72) return &font_bold_italic_24x64;
        else if (height < 95) return &font_bold_italic_30x80;
        //else return &font_regular_44x120;
    } else if (bold && !italic) {
        if (height < 7) return &font_regular_4x6;
        else if (height < 10) return &font_regular_6x8;
        else if (height < 14) return &font_regular_8x12;
        else if (height < 22) return &font_regular_10x16;
        else if (height < 33) return &font_bold_12x30;
        else if (height < 39) return &font_bold_14x36;
        else if (height < 47) return &font_bold_16x42;
        else if (height < 58) return &font_bold_20x52;
        else if (height < 72) return &font_bold_24x64;
        else if (height < 95) return &font_bold_30x80;
        //else return &font_bold_44x120;
    } else if (!bold && italic) {
        if (height < 7) return &font_regular_4x6;
        else if (height < 10) return &font_regular_6x8;
        else if (height < 14) return &font_regular_8x12;
        else if (height < 22) return &font_regular_10x16;
        else if (height < 33) return &font_italic_12x30;
        else if (height < 39) return &font_italic_14x36;
        else if (height < 47) return &font_italic_16x42;
        else if (height < 58) return &font_italic_20x52;
        else if (height < 72) return &font_italic_24x64;
        else if (height < 95) return &font_italic_30x80;
        //else return &font_italic_44x120;
    } else {
        if (height < 7) return &font_regular_4x6;
        else if (height < 10) return &font_regular_6x8;
        else if (height < 14) return &font_regular_8x12;
        else if (height < 22) return &font_regular_10x16;
        else if (height < 33) return &font_regular_12x30;
        else if (height < 39) return &font_regular_14x36;
        else if (height < 47) return &font_regular_16x42;
        else if (height < 58) return &font_regular_20x52;
        else if (height < 72) return &font_regular_24x64;
        else if (height < 95) return &font_regular_30x80;
        //else return &font_regular_44x120;
    }
    return &font_regular_30x80;
}
