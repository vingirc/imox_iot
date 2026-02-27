/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --font C:/Users/irvin/OneDrive/Documentos/tareas8/imox_square-line_ui/assets/Qualy Bold.ttf -o C:/Users/irvin/OneDrive/Documentos/tareas8/imox_square-line_ui/assets\ui_font_Qualy14.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_QUALY14
#define UI_FONT_QUALY14 1
#endif

#if UI_FONT_QUALY14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xf0,

    /* U+0022 "\"" */
    0xff, 0x5a,

    /* U+0023 "#" */
    0x34, 0x48, 0x97, 0xff, 0xff, 0xff, 0xb4, 0x48,
    0x90,

    /* U+0024 "$" */
    0x10, 0x79, 0x97, 0x7, 0xf, 0x87, 0x87, 0x6,
    0x8d, 0xf0, 0x80,

    /* U+0025 "%" */
    0x60, 0xd2, 0x32, 0x44, 0x31, 0x0, 0x60, 0x1b,
    0x82, 0x88, 0x91, 0x32, 0x2c, 0x39, 0x0, 0x0,

    /* U+0026 "&" */
    0x38, 0x3e, 0x1b, 0x5, 0x7, 0x7, 0xf3, 0x3d,
    0xfe, 0x7b, 0x0,

    /* U+0027 "'" */
    0xf6,

    /* U+0028 "(" */
    0x26, 0xcc, 0xcc, 0xcc, 0x62,

    /* U+0029 ")" */
    0x46, 0x33, 0x33, 0x33, 0x64,

    /* U+002A "*" */
    0x27, 0xc9, 0xf2, 0x0,

    /* U+002B "+" */
    0x30, 0xcf, 0xff, 0x30, 0xc0,

    /* U+002C "," */
    0x58,

    /* U+002D "-" */
    0xff, 0xc0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x18, 0xc4, 0x63, 0x11, 0x88, 0x46, 0x0,

    /* U+0030 "0" */
    0x38, 0xfb, 0xbe, 0x3c, 0x78, 0xf1, 0xf7, 0x7c,
    0x70,

    /* U+0031 "1" */
    0x7f, 0x33, 0x33, 0x33, 0x33,

    /* U+0032 "2" */
    0x3c, 0xff, 0x1e, 0x30, 0x61, 0x86, 0x18, 0xff,
    0xfc,

    /* U+0033 "3" */
    0x38, 0xf9, 0xb0, 0x61, 0x81, 0xc1, 0xf3, 0x7e,
    0x78,

    /* U+0034 "4" */
    0xc, 0x30, 0xc1, 0xa6, 0xd9, 0xbf, 0xff, 0xc,
    0x18,

    /* U+0035 "5" */
    0x3e, 0x7c, 0x83, 0xe7, 0xe4, 0xc1, 0xe3, 0x7c,
    0x70,

    /* U+0036 "6" */
    0x18, 0xc3, 0x18, 0x7b, 0xfc, 0xf3, 0xfd, 0xe0,

    /* U+0037 "7" */
    0xff, 0xf0, 0x86, 0x10, 0xc3, 0x18, 0x63, 0x0,

    /* U+0038 "8" */
    0x79, 0xfb, 0x36, 0x67, 0xcf, 0xb1, 0xe3, 0xfe,
    0xf8,

    /* U+0039 "9" */
    0x7b, 0xfc, 0xf3, 0xfd, 0xe1, 0x8c, 0x31, 0x80,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xe, 0x80,

    /* U+003C "<" */
    0x6, 0x3d, 0xe7, 0xe, 0x7, 0x7, 0x83,

    /* U+003D "=" */
    0xff, 0xf0, 0x3f, 0xfc,

    /* U+003E ">" */
    0x81, 0xc0, 0xe0, 0x70, 0xe7, 0x38, 0x40,

    /* U+003F "?" */
    0x7b, 0xfc, 0xc3, 0x18, 0xc3, 0x0, 0x30, 0xc0,

    /* U+0040 "@" */
    0x1f, 0x18, 0x65, 0xde, 0xfd, 0xb3, 0x6c, 0x9b,
    0xe9, 0x6c, 0x61, 0x87, 0x80,

    /* U+0041 "A" */
    0xc, 0xc, 0x6, 0x86, 0x43, 0x61, 0x99, 0xfc,
    0xfe, 0x61, 0xe0, 0xc0,

    /* U+0042 "B" */
    0xf9, 0xfb, 0x36, 0x6f, 0x9f, 0xb1, 0xe3, 0xff,
    0xf8,

    /* U+0043 "C" */
    0x1e, 0x3f, 0x98, 0x78, 0xc, 0x6, 0x3, 0x0,
    0xc3, 0x7f, 0xf, 0x0,

    /* U+0044 "D" */
    0xfc, 0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6,
    0xfe, 0xf8,

    /* U+0045 "E" */
    0xff, 0xfc, 0x30, 0xff, 0xfc, 0x30, 0xff, 0xf0,

    /* U+0046 "F" */
    0xff, 0xfc, 0x30, 0xff, 0xfc, 0x30, 0xc3, 0x0,

    /* U+0047 "G" */
    0x1e, 0x1f, 0xc6, 0x13, 0x0, 0xc0, 0x31, 0xfc,
    0x7d, 0x86, 0x7f, 0x87, 0x80,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3f, 0xff, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+0049 "I" */
    0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0xff, 0x80,

    /* U+004B "K" */
    0xc7, 0x9b, 0x76, 0xcf, 0x1e, 0x36, 0x6e, 0xcd,
    0x8c,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xff, 0xf0,

    /* U+004D "M" */
    0x30, 0xce, 0x19, 0xc7, 0x3c, 0xe7, 0x96, 0xf6,
    0xd3, 0xde, 0x73, 0xce, 0x78, 0xc4,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xf3, 0xdb, 0xdb, 0xcf, 0xc7,
    0xc7, 0xc3,

    /* U+004F "O" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xd, 0x86, 0x7f, 0x87, 0x80,

    /* U+0050 "P" */
    0xf9, 0xfb, 0x1e, 0x3c, 0x7f, 0xbe, 0x60, 0xc1,
    0x80,

    /* U+0051 "Q" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0x6d, 0x8e, 0x79, 0x87, 0x70,

    /* U+0052 "R" */
    0xf9, 0xfb, 0x1e, 0x3c, 0x7f, 0xbe, 0x6e, 0xcd,
    0x8c,

    /* U+0053 "S" */
    0x73, 0xec, 0x30, 0x70, 0xe1, 0xb3, 0xf9, 0xc0,

    /* U+0054 "T" */
    0xff, 0xfc, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x7c,
    0x70,

    /* U+0056 "V" */
    0xc1, 0xa1, 0x98, 0xcc, 0x62, 0x61, 0xb0, 0xc8,
    0x30, 0x18, 0xc, 0x0,

    /* U+0057 "W" */
    0xc6, 0x3c, 0x66, 0x4e, 0x66, 0xf6, 0x6f, 0x67,
    0xb4, 0x79, 0xc3, 0x9c, 0x31, 0xc3, 0x1c,

    /* U+0058 "X" */
    0x63, 0x33, 0x8d, 0x87, 0x1, 0x80, 0xe0, 0xf8,
    0x6c, 0x63, 0x61, 0x80,

    /* U+0059 "Y" */
    0xc3, 0x66, 0x66, 0x34, 0x38, 0x18, 0x18, 0x18,
    0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0xe1, 0x8c, 0x30, 0x86, 0x18, 0xff, 0xf0,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xff,

    /* U+005C "\\" */
    0x18, 0xc4, 0x63, 0x11, 0x88, 0x46, 0x0,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0xff,

    /* U+005E "^" */
    0x10, 0x60, 0xe1, 0xc6, 0x89, 0xb3, 0x62,

    /* U+005F "_" */
    0xff, 0xfc,

    /* U+0060 "`" */
    0xc6, 0x20,

    /* U+0061 "a" */
    0xc, 0xc, 0x6, 0x86, 0x43, 0x61, 0x99, 0xfc,
    0xfe, 0x61, 0xe0, 0xc0,

    /* U+0062 "b" */
    0xf9, 0xfb, 0x36, 0x6f, 0x9f, 0xb1, 0xe3, 0xff,
    0xf8,

    /* U+0063 "c" */
    0x1e, 0x3f, 0x98, 0x78, 0xc, 0x6, 0x3, 0x0,
    0xc3, 0x7f, 0xf, 0x0,

    /* U+0064 "d" */
    0xfc, 0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6,
    0xfe, 0xf8,

    /* U+0065 "e" */
    0xff, 0xfc, 0x30, 0xff, 0xfc, 0x30, 0xff, 0xf0,

    /* U+0066 "f" */
    0xff, 0xfc, 0x30, 0xff, 0xfc, 0x30, 0xc3, 0x0,

    /* U+0067 "g" */
    0x1e, 0x1f, 0xc6, 0x13, 0x0, 0xc0, 0x31, 0xfc,
    0x7d, 0x86, 0x7f, 0x87, 0x80,

    /* U+0068 "h" */
    0xc7, 0x8f, 0x1e, 0x3f, 0xff, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+0069 "i" */
    0xff, 0xff, 0xf0,

    /* U+006A "j" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0xff, 0x80,

    /* U+006B "k" */
    0xc7, 0x9b, 0x76, 0xcf, 0x1e, 0x36, 0x6e, 0xcd,
    0x8c,

    /* U+006C "l" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xff, 0xf0,

    /* U+006D "m" */
    0x30, 0xce, 0x19, 0xc7, 0x3c, 0xe7, 0x96, 0xf6,
    0xd3, 0xde, 0x73, 0xce, 0x78, 0xc4,

    /* U+006E "n" */
    0xc3, 0xe3, 0xe3, 0xf3, 0xdb, 0xdb, 0xcf, 0xc7,
    0xc7, 0xc3,

    /* U+006F "o" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xd, 0x86, 0x7f, 0x87, 0x80,

    /* U+0070 "p" */
    0xf9, 0xfb, 0x1e, 0x3c, 0x7f, 0xbe, 0x60, 0xc1,
    0x80,

    /* U+0071 "q" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0x6d, 0x8e, 0x79, 0x87, 0x70,

    /* U+0072 "r" */
    0xf9, 0xfb, 0x1e, 0x3c, 0x7f, 0xbe, 0x6e, 0xcd,
    0x8c,

    /* U+0073 "s" */
    0x73, 0xec, 0x30, 0x70, 0xe1, 0xb3, 0xf9, 0xc0,

    /* U+0074 "t" */
    0xff, 0xfc, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x7c,
    0x70,

    /* U+0076 "v" */
    0xc1, 0xa1, 0x98, 0xcc, 0x62, 0x61, 0xb0, 0xc8,
    0x30, 0x18, 0xc, 0x0,

    /* U+0077 "w" */
    0xc6, 0x3c, 0x66, 0x4e, 0x66, 0xf6, 0x6f, 0x67,
    0xb4, 0x79, 0xc3, 0x9c, 0x31, 0xc3, 0x1c,

    /* U+0078 "x" */
    0x63, 0x33, 0x8d, 0x87, 0x1, 0x80, 0xe0, 0xf8,
    0x6c, 0x63, 0x61, 0x80,

    /* U+0079 "y" */
    0xc3, 0x66, 0x66, 0x34, 0x38, 0x18, 0x18, 0x18,
    0x18, 0x18,

    /* U+007A "z" */
    0xff, 0xe1, 0x8c, 0x30, 0x86, 0x18, 0xff, 0xf0,

    /* U+007B "{" */
    0x36, 0x66, 0x6c, 0x66, 0x67,

    /* U+007C "|" */
    0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xe6, 0x66, 0x33, 0x66, 0x6e,

    /* U+007E "~" */
    0xf1, 0xfc, 0x78
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 66, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 57, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 90, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 136, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 196, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 42, .adv_w = 151, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 48, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 54, .adv_w = 87, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 88, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 105, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 68, .adv_w = 126, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 73, .adv_w = 62, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 74, .adv_w = 74, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 76, .adv_w = 54, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 110, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 82, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 126, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 122, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 55, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 61, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 172, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 179, .adv_w = 126, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 183, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 190, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 178, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 169, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 172, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 50, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 102, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 175, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 180, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 159, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 202, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 100, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 110, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 100, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 494, .adv_w = 130, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 498, .adv_w = 169, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 174, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 50, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 102, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 175, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 180, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 159, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 202, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 71, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 39, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 72, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 4}
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
    .cmap_num = 1,
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
const lv_font_t ui_font_Qualy14 = {
#else
lv_font_t ui_font_Qualy14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if UI_FONT_QUALY14*/

