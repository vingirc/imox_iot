/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:/Users/irvin/OneDrive/Documentos/tareas8/imox_square-line_ui/assets/RobotoMono-Bold.ttf -o C:/Users/irvin/OneDrive/Documentos/tareas8/imox_square-line_ui/assets\ui_font_LecturaS.c --format lvgl -r 0x20-0x7f -r 0x3a6 --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_LECTURAS
#define UI_FONT_LECTURAS 1
#endif

#if UI_FONT_LECTURAS

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xf,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x1a, 0x9, 0x4, 0x8f, 0xf7, 0xf8, 0xb0, 0xd1,
    0xfe, 0xff, 0x12, 0x9, 0x5, 0x80,

    /* U+0024 "$" */
    0x8, 0x8, 0x3e, 0x63, 0x63, 0x60, 0x78, 0x3e,
    0xf, 0x3, 0x63, 0x63, 0x7e, 0x8, 0x8,

    /* U+0025 "%" */
    0x70, 0x7c, 0x36, 0x9f, 0x87, 0x40, 0x40, 0x2c,
    0x2f, 0x15, 0x82, 0xc1, 0xe0, 0x60,

    /* U+0026 "&" */
    0x3c, 0x3f, 0x19, 0x8c, 0xc7, 0xc1, 0xc1, 0xe7,
    0xdb, 0xcf, 0xf3, 0xbf, 0xcf, 0xf0,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x13, 0x66, 0x4c, 0xcc, 0xcc, 0xcc, 0x66, 0x33,
    0x0,

    /* U+0029 ")" */
    0x8c, 0x66, 0x23, 0x33, 0x33, 0x33, 0x66, 0xcc,
    0x0,

    /* U+002A "*" */
    0x18, 0x18, 0x9, 0xff, 0x1c, 0x1c, 0x36, 0x66,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0x6d, 0xbc,

    /* U+002D "-" */
    0xff, 0xfc,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0xc, 0x71, 0x86, 0x38, 0xc3, 0xc, 0x61, 0x86,
    0x30, 0xc0,

    /* U+0030 "0" */
    0x38, 0xfb, 0x1e, 0x3c, 0x7b, 0xfd, 0xe3, 0xc7,
    0x8d, 0xf1, 0xc0,

    /* U+0031 "1" */
    0xb, 0xff, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0032 "2" */
    0x3c, 0x7e, 0xe3, 0xc3, 0x3, 0x6, 0xe, 0x1c,
    0x38, 0x70, 0xff, 0xff,

    /* U+0033 "3" */
    0x3c, 0x7f, 0x63, 0x3, 0x3, 0x1e, 0x1e, 0x3,
    0x3, 0x63, 0x7e, 0x3c,

    /* U+0034 "4" */
    0x6, 0xe, 0x1e, 0x1e, 0x36, 0x36, 0x66, 0x46,
    0xff, 0xff, 0x6, 0x6,

    /* U+0035 "5" */
    0xff, 0xff, 0x6, 0xf, 0xdf, 0xd3, 0x83, 0x7,
    0x8f, 0xfb, 0xc0,

    /* U+0036 "6" */
    0x1c, 0x3c, 0x70, 0x60, 0xdc, 0xfe, 0xe7, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0x7, 0x6, 0x6, 0xc, 0xc, 0x18,
    0x18, 0x38, 0x30, 0x70,

    /* U+0038 "8" */
    0x7d, 0xff, 0x1e, 0x3c, 0x6f, 0x9f, 0x63, 0xc7,
    0x8f, 0xfb, 0xe0,

    /* U+0039 "9" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe3, 0x7f, 0x3b,
    0x6, 0xe, 0x3c, 0x38,

    /* U+003A ":" */
    0xff, 0x80, 0x7, 0xfc,

    /* U+003B ";" */
    0xff, 0x80, 0x6, 0xdb, 0x48,

    /* U+003C "<" */
    0x2, 0x3d, 0xf7, 0xf, 0x7, 0xc3, 0x81,

    /* U+003D "=" */
    0xff, 0xfc, 0x7, 0xff, 0xe0,

    /* U+003E ">" */
    0x81, 0xe1, 0xf0, 0x71, 0xff, 0x38, 0x40,

    /* U+003F "?" */
    0x3e, 0x7f, 0x63, 0x3, 0x3, 0x6, 0xc, 0x18,
    0x18, 0x0, 0x18, 0x18,

    /* U+0040 "@" */
    0x1e, 0x18, 0x98, 0x39, 0xdd, 0xae, 0x97, 0x4b,
    0xa5, 0xdf, 0x30, 0x1f, 0x87, 0x80,

    /* U+0041 "A" */
    0xc, 0x7, 0x1, 0xe0, 0x78, 0x1e, 0xd, 0xc3,
    0x30, 0xcc, 0x7f, 0x9f, 0xe6, 0x1b, 0x86,

    /* U+0042 "B" */
    0xfc, 0xff, 0xc3, 0xc3, 0xc3, 0xfe, 0xfe, 0xc3,
    0xc3, 0xc3, 0xfe, 0xfc,

    /* U+0043 "C" */
    0x3e, 0x3f, 0x98, 0xd8, 0x6c, 0x6, 0x3, 0x1,
    0x80, 0xc3, 0x71, 0x9f, 0xc7, 0xc0,

    /* U+0044 "D" */
    0xf8, 0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc6, 0xfe, 0xf8,

    /* U+0045 "E" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0,
    0xc0, 0xc0, 0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0x3c, 0x7e, 0xe3, 0xc3, 0xc0, 0xc0, 0xcf, 0xcf,
    0xc3, 0xe3, 0x7f, 0x3e,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xff, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+0049 "I" */
    0xff, 0xfc, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x63, 0xff, 0xf0,

    /* U+004A "J" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
    0xe3, 0x67, 0x7e, 0x3c,

    /* U+004B "K" */
    0xc7, 0x63, 0x33, 0x9b, 0x8d, 0x87, 0xc3, 0xe1,
    0xf8, 0xce, 0x63, 0x31, 0xd8, 0x60,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xff, 0xff,

    /* U+004D "M" */
    0xe7, 0xe7, 0xef, 0xff, 0xff, 0xdb, 0xdb, 0xdb,
    0xc3, 0xc3, 0xc3, 0xc3,

    /* U+004E "N" */
    0xc7, 0xcf, 0x9f, 0x3f, 0x7e, 0xf7, 0xef, 0xcf,
    0x9f, 0x3e, 0x30,

    /* U+004F "O" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xfc,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3e, 0x3, 0x1,

    /* U+0052 "R" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xfc,
    0xce, 0xc6, 0xc7, 0xc3,

    /* U+0053 "S" */
    0x1e, 0x1f, 0x98, 0xec, 0x37, 0x1, 0xe0, 0x3c,
    0x7, 0xe1, 0xb0, 0xdf, 0xe3, 0xc0,

    /* U+0054 "T" */
    0xff, 0xff, 0xc3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x1, 0x80,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0056 "V" */
    0xe1, 0xb0, 0xd8, 0xee, 0x63, 0x31, 0x98, 0xdc,
    0x7c, 0x1e, 0xf, 0x7, 0x1, 0x80,

    /* U+0057 "W" */
    0xcd, 0xe6, 0xdb, 0x6d, 0xb7, 0xdb, 0xed, 0xf6,
    0xee, 0x77, 0x3b, 0x8c, 0xc6, 0x60,

    /* U+0058 "X" */
    0x61, 0x9c, 0xe3, 0x30, 0xfc, 0x1e, 0x7, 0x81,
    0xe0, 0x78, 0x37, 0xc, 0xc7, 0x3b, 0x86,

    /* U+0059 "Y" */
    0x61, 0x98, 0x63, 0x30, 0xcc, 0x1f, 0x7, 0x81,
    0xe0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xff, 0xff, 0x6, 0xe, 0xc, 0x18, 0x18, 0x30,
    0x70, 0x60, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,
    0xf0,

    /* U+005C "\\" */
    0xc3, 0x6, 0x18, 0x60, 0xc3, 0xc, 0x18, 0x61,
    0x83, 0xc,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,
    0xf0,

    /* U+005E "^" */
    0x30, 0xc7, 0x9e, 0x4b, 0x3c, 0xc0,

    /* U+005F "_" */
    0xff, 0xfc,

    /* U+0060 "`" */
    0x63,

    /* U+0061 "a" */
    0x7d, 0xff, 0x1b, 0xff, 0xf8, 0xf1, 0xff, 0x7e,

    /* U+0062 "b" */
    0xc1, 0x83, 0x6, 0xef, 0xd9, 0xf1, 0xe3, 0xc7,
    0x8f, 0xf7, 0xe0,

    /* U+0063 "c" */
    0x3c, 0x7e, 0xe6, 0xc0, 0xc0, 0xc0, 0xe6, 0x7e,
    0x3c,

    /* U+0064 "d" */
    0x6, 0xc, 0x19, 0xb7, 0xfc, 0xf1, 0xe3, 0xc7,
    0xcd, 0xfb, 0xb0,

    /* U+0065 "e" */
    0x3c, 0x7e, 0xe3, 0xff, 0xff, 0xc0, 0xe2, 0x7f,
    0x3c,

    /* U+0066 "f" */
    0x1f, 0x1e, 0x30, 0x30, 0xfe, 0xfe, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30,

    /* U+0067 "g" */
    0x3f, 0x7f, 0xe3, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f,
    0x3b, 0x47, 0x7e, 0x3c,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xef, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+0069 "i" */
    0x18, 0x30, 0x7, 0xcf, 0x83, 0x6, 0xc, 0x18,
    0x33, 0xff, 0xf0,

    /* U+006A "j" */
    0x18, 0xc0, 0xf7, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0xff, 0xc0,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xd8, 0xf8, 0xf8,
    0xfc, 0xcc, 0xce, 0xc7,

    /* U+006C "l" */
    0xf9, 0xf0, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x33, 0xff, 0xf0,

    /* U+006D "m" */
    0xfe, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb,

    /* U+006E "n" */
    0xdd, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0070 "p" */
    0xfd, 0xfb, 0x3e, 0x3c, 0x78, 0xf3, 0xfe, 0xf9,
    0x83, 0x6, 0x0,

    /* U+0071 "q" */
    0x3e, 0xff, 0x9e, 0x3c, 0x78, 0xf9, 0xbf, 0x7e,
    0xc, 0x18, 0x30,

    /* U+0072 "r" */
    0xdf, 0xfe, 0x30, 0xc3, 0xc, 0x30, 0xc0,

    /* U+0073 "s" */
    0x3c, 0x7e, 0xc6, 0x60, 0x3c, 0x6, 0xe2, 0x7e,
    0x3c,

    /* U+0074 "t" */
    0x30, 0x63, 0xff, 0xf3, 0x6, 0xc, 0x18, 0x30,
    0x7c, 0x78,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0x76,

    /* U+0076 "v" */
    0xc3, 0xc7, 0xe6, 0x66, 0x6c, 0x2c, 0x3c, 0x38,
    0x18,

    /* U+0077 "w" */
    0xcd, 0xe6, 0xdb, 0x6f, 0xb7, 0x53, 0xa9, 0xdc,
    0xe6, 0x33, 0x0,

    /* U+0078 "x" */
    0xc7, 0x66, 0x7e, 0x3c, 0x18, 0x3c, 0x7e, 0x66,
    0xc3,

    /* U+0079 "y" */
    0x61, 0x98, 0x63, 0x38, 0xcc, 0x3f, 0x7, 0x81,
    0xe0, 0x30, 0xc, 0x6, 0x3, 0x81, 0xc0,

    /* U+007A "z" */
    0xff, 0xff, 0xe, 0xc, 0x18, 0x30, 0x60, 0xff,
    0xff,

    /* U+007B "{" */
    0x19, 0xcc, 0x63, 0x18, 0xdc, 0xe1, 0x8c, 0x63,
    0x18, 0x63,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xc7, 0x18, 0xc6, 0x31, 0x87, 0x3b, 0x18, 0xc6,
    0x33, 0x18,

    /* U+007E "~" */
    0x70, 0x7c, 0xb3, 0xc0, 0xc0,

    /* U+03A6 "Φ" */
    0xc, 0x3, 0x3, 0xf1, 0xfe, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0x7f, 0x8f, 0xc0, 0xc0, 0x30
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 154, .box_w = 2, .box_h = 12, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 154, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 7, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 154, .box_w = 2, .box_h = 4, .ofs_x = 4, .ofs_y = 8},
    {.bitmap_index = 65, .adv_w = 154, .box_w = 4, .box_h = 17, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 74, .adv_w = 154, .box_w = 4, .box_h = 17, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 83, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 91, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 99, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 101, .adv_w = 154, .box_w = 7, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 103, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 154, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 115, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 154, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 154, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 154, .box_w = 3, .box_h = 13, .ofs_x = 4, .ofs_y = -3},
    {.bitmap_index = 237, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 244, .adv_w = 154, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 249, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 256, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 492, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 154, .box_w = 4, .box_h = 17, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 623, .adv_w = 154, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 633, .adv_w = 154, .box_w = 4, .box_h = 17, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 642, .adv_w = 154, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 648, .adv_w = 154, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 650, .adv_w = 154, .box_w = 4, .box_h = 2, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 651, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 724, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 756, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 805, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 816, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 827, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 834, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 843, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 870, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 881, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 890, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 905, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 154, .box_w = 5, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 924, .adv_w = 154, .box_w = 2, .box_h = 15, .ofs_x = 4, .ofs_y = -3},
    {.bitmap_index = 928, .adv_w = 154, .box_w = 5, .box_h = 16, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 938, .adv_w = 154, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 943, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 934, .range_length = 1, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_LecturaS = {
#else
lv_font_t ui_font_LecturaS = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_LECTURAS*/

