/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:/Users/irvin/OneDrive/Documentos/tareas8/imox_square-line_ui/assets/Qualy Bold.ttf -o C:/Users/irvin/OneDrive/Documentos/tareas8/imox_square-line_ui/assets\ui_font_LecturaS.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
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
    0xff, 0xff, 0x3c,

    /* U+0022 "\"" */
    0xde, 0xd3, 0x20,

    /* U+0023 "#" */
    0x12, 0x36, 0x36, 0xff, 0xff, 0x26, 0xff, 0xff,
    0x6c, 0x6c, 0x4c,

    /* U+0024 "$" */
    0x3c, 0x7e, 0x62, 0x60, 0x78, 0x3e, 0xf, 0x3,
    0x3, 0x63, 0x7e, 0x8,

    /* U+0025 "%" */
    0x78, 0x27, 0xe2, 0x33, 0x21, 0xfb, 0x7, 0x90,
    0x1, 0x0, 0x1b, 0xc1, 0xbf, 0x9, 0x98, 0x8f,
    0xcc, 0x3c, 0x40, 0x0,

    /* U+0026 "&" */
    0x38, 0x3e, 0x1b, 0xd, 0x83, 0x83, 0xc3, 0x3d,
    0x9e, 0xff, 0x3d, 0xc0,

    /* U+0027 "'" */
    0xf6,

    /* U+0028 "(" */
    0x36, 0xcc, 0xcc, 0xcc, 0x46, 0x30,

    /* U+0029 ")" */
    0xc6, 0x23, 0x33, 0x33, 0x76, 0xc0,

    /* U+002A "*" */
    0x33, 0x73, 0x3b, 0x30,

    /* U+002B "+" */
    0x18, 0x33, 0xff, 0xf1, 0x83, 0x6, 0x0,

    /* U+002C "," */
    0x6b, 0x0,

    /* U+002D "-" */
    0xff, 0xc0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x21, 0x86, 0x30, 0xc2, 0x18, 0x61, 0xc,
    0x0,

    /* U+0030 "0" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7e, 0x3c,

    /* U+0031 "1" */
    0x7f, 0x33, 0x33, 0x33, 0x33, 0x30,

    /* U+0032 "2" */
    0x3c, 0xff, 0x9e, 0x30, 0x61, 0x87, 0x1c, 0x71,
    0xff, 0xf8,

    /* U+0033 "3" */
    0x3c, 0x7e, 0x66, 0x6, 0x1e, 0x1e, 0x3, 0x63,
    0x63, 0x7e, 0x3c,

    /* U+0034 "4" */
    0x6, 0xc, 0x1c, 0x38, 0x32, 0x66, 0xe6, 0xff,
    0xff, 0x6, 0x6,

    /* U+0035 "5" */
    0x3e, 0xfd, 0x83, 0x7, 0x8f, 0x81, 0x83, 0xc7,
    0xf9, 0xe0,

    /* U+0036 "6" */
    0x1c, 0x30, 0xe1, 0x87, 0x8f, 0xb1, 0xe3, 0xc6,
    0xf8, 0xe0,

    /* U+0037 "7" */
    0xff, 0xfc, 0x30, 0x61, 0x83, 0xc, 0x18, 0x60,
    0xc3, 0x80,

    /* U+0038 "8" */
    0x3c, 0x7e, 0x66, 0x66, 0x7e, 0x7e, 0xe7, 0xc3,
    0xe3, 0x7e, 0x3c,

    /* U+0039 "9" */
    0x38, 0xfb, 0x1e, 0x3c, 0x6f, 0x8f, 0xc, 0x18,
    0x61, 0xc0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0x7, 0xa0,

    /* U+003C "<" */
    0x3, 0xf, 0x3c, 0xf0, 0xc0, 0x70, 0x1c, 0x7,
    0x1,

    /* U+003D "=" */
    0xff, 0xfc, 0x7, 0xff, 0xe0,

    /* U+003E ">" */
    0x80, 0xe0, 0x78, 0x1e, 0x7, 0x1e, 0x78, 0xe0,
    0x80,

    /* U+003F "?" */
    0x3c, 0xff, 0x18, 0x30, 0xe3, 0x86, 0x18, 0x0,
    0x70, 0xc0,

    /* U+0040 "@" */
    0x1f, 0x4, 0x19, 0x3f, 0x4f, 0xdb, 0x33, 0x62,
    0x6c, 0xd5, 0xfe, 0x49, 0x6, 0x18, 0x7c, 0x0,

    /* U+0041 "A" */
    0xc, 0x1, 0x80, 0x70, 0xc, 0x81, 0xb0, 0x67,
    0xc, 0x63, 0xfc, 0x7f, 0xcc, 0x1b, 0x3, 0x80,

    /* U+0042 "B" */
    0xfc, 0xfe, 0xc6, 0xc6, 0xfc, 0xfe, 0xc7, 0xc3,
    0xc3, 0xfe, 0xfc,

    /* U+0043 "C" */
    0x1f, 0xf, 0xe7, 0xf, 0x80, 0xc0, 0x30, 0xc,
    0x3, 0x80, 0x70, 0xcf, 0xe1, 0xf0,

    /* U+0044 "D" */
    0xfc, 0x7f, 0xb1, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc7, 0x7f, 0xbf, 0x0,

    /* U+0045 "E" */
    0xff, 0xff, 0x6, 0xf, 0xff, 0xf0, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+0046 "F" */
    0xff, 0xfc, 0x30, 0xff, 0xfc, 0x30, 0xc3, 0xc,
    0x0,

    /* U+0047 "G" */
    0x1f, 0x7, 0xf1, 0xc4, 0x70, 0xc, 0x1, 0x8f,
    0xf1, 0xff, 0x7, 0x71, 0xc7, 0xf0, 0x7c, 0x0,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf, 0xff,
    0x80,

    /* U+004B "K" */
    0xc7, 0xce, 0xcc, 0xdc, 0xf8, 0xf0, 0xf8, 0xdc,
    0xcc, 0xce, 0xc7,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xff,
    0xc0,

    /* U+004D "M" */
    0x30, 0x61, 0xc3, 0x1e, 0x3c, 0xf1, 0xe7, 0xcf,
    0x36, 0xd9, 0xb6, 0xcd, 0xf7, 0xe7, 0x1e, 0x38,
    0xf0, 0xc6,

    /* U+004E "N" */
    0xc1, 0xf0, 0xfc, 0x7e, 0x3f, 0x9e, 0xef, 0x37,
    0x8f, 0xc7, 0xe1, 0xf0, 0x60,

    /* U+004F "O" */
    0x1f, 0x7, 0xf1, 0xc7, 0x70, 0x7c, 0x7, 0x80,
    0xf0, 0x1f, 0x7, 0x71, 0xc7, 0xf0, 0x7c, 0x0,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xfe, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1f, 0x7, 0xf1, 0xc7, 0x70, 0x7c, 0x7, 0x80,
    0xf1, 0xdf, 0x1f, 0x71, 0xc7, 0xb8, 0x73, 0x80,

    /* U+0052 "R" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc7, 0xfe, 0xfc, 0xcc,
    0xce, 0xc6, 0xc3,

    /* U+0053 "S" */
    0x38, 0xfd, 0x93, 0x3, 0x83, 0x83, 0x83, 0x66,
    0xfc, 0xf0,

    /* U+0054 "T" */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7e, 0x3c,

    /* U+0056 "V" */
    0xc0, 0xd8, 0x76, 0x19, 0x86, 0x33, 0xc, 0xc3,
    0xb0, 0x68, 0x18, 0x7, 0x0, 0xc0,

    /* U+0057 "W" */
    0xc3, 0x1e, 0x38, 0xd9, 0xc6, 0xce, 0x76, 0xdb,
    0x36, 0xd8, 0xf6, 0xc7, 0x9e, 0x38, 0xe1, 0xc7,
    0xe, 0x18,

    /* U+0058 "X" */
    0x61, 0x9c, 0xe3, 0x30, 0x68, 0x1c, 0x3, 0x1,
    0xe0, 0xfc, 0x33, 0x18, 0x6e, 0x1c,

    /* U+0059 "Y" */
    0xc3, 0x67, 0x66, 0x34, 0x30, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0xf8, 0x70, 0xc1, 0x86, 0xc, 0x30, 0x61,
    0xff, 0xf8,

    /* U+005B "[" */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc7, 0xfe,

    /* U+005C "\\" */
    0xc, 0x21, 0x86, 0x30, 0xc2, 0x18, 0x61, 0xc,
    0x0,

    /* U+005D "]" */
    0xff, 0xc6, 0x31, 0x8c, 0x63, 0x1f, 0xfe,

    /* U+005E "^" */
    0x18, 0x38, 0x3c, 0x2c, 0x6c, 0x66, 0x46, 0xc2,

    /* U+005F "_" */
    0xff, 0xff,

    /* U+0060 "`" */
    0xe6, 0x30,

    /* U+0061 "a" */
    0xc, 0x1, 0x80, 0x70, 0xc, 0x81, 0xb0, 0x67,
    0xc, 0x63, 0xfc, 0x7f, 0xcc, 0x1b, 0x3, 0x80,

    /* U+0062 "b" */
    0xfc, 0xfe, 0xc6, 0xc6, 0xfc, 0xfe, 0xc7, 0xc3,
    0xc3, 0xfe, 0xfc,

    /* U+0063 "c" */
    0x1f, 0xf, 0xe7, 0xf, 0x80, 0xc0, 0x30, 0xc,
    0x3, 0x80, 0x70, 0xcf, 0xe1, 0xf0,

    /* U+0064 "d" */
    0xfc, 0x7f, 0xb1, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc7, 0x7f, 0xbf, 0x0,

    /* U+0065 "e" */
    0xff, 0xff, 0x6, 0xf, 0xff, 0xf0, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+0066 "f" */
    0xff, 0xfc, 0x30, 0xff, 0xfc, 0x30, 0xc3, 0xc,
    0x0,

    /* U+0067 "g" */
    0x1f, 0x7, 0xf1, 0xc4, 0x70, 0xc, 0x1, 0x8f,
    0xf1, 0xff, 0x7, 0x71, 0xc7, 0xf0, 0x7c, 0x0,

    /* U+0068 "h" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xff, 0xff, 0xfc,

    /* U+006A "j" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf, 0xff,
    0x80,

    /* U+006B "k" */
    0xc7, 0xce, 0xcc, 0xdc, 0xf8, 0xf0, 0xf8, 0xdc,
    0xcc, 0xce, 0xc7,

    /* U+006C "l" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xff,
    0xc0,

    /* U+006D "m" */
    0x30, 0x61, 0xc3, 0x1e, 0x3c, 0xf1, 0xe7, 0xcf,
    0x36, 0xd9, 0xb6, 0xcd, 0xf7, 0xe7, 0x1e, 0x38,
    0xf0, 0xc6,

    /* U+006E "n" */
    0xc1, 0xf0, 0xfc, 0x7e, 0x3f, 0x9e, 0xef, 0x37,
    0x8f, 0xc7, 0xe1, 0xf0, 0x60,

    /* U+006F "o" */
    0x1f, 0x7, 0xf1, 0xc7, 0x70, 0x7c, 0x7, 0x80,
    0xf0, 0x1f, 0x7, 0x71, 0xc7, 0xf0, 0x7c, 0x0,

    /* U+0070 "p" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xfe, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x1f, 0x7, 0xf1, 0xc7, 0x70, 0x7c, 0x7, 0x80,
    0xf1, 0xdf, 0x1f, 0x71, 0xc7, 0xb8, 0x73, 0x80,

    /* U+0072 "r" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc7, 0xfe, 0xfc, 0xcc,
    0xce, 0xc6, 0xc3,

    /* U+0073 "s" */
    0x38, 0xfd, 0x93, 0x3, 0x83, 0x83, 0x83, 0x66,
    0xfc, 0xf0,

    /* U+0074 "t" */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7e, 0x3c,

    /* U+0076 "v" */
    0xc0, 0xd8, 0x76, 0x19, 0x86, 0x33, 0xc, 0xc3,
    0xb0, 0x68, 0x18, 0x7, 0x0, 0xc0,

    /* U+0077 "w" */
    0xc3, 0x1e, 0x38, 0xd9, 0xc6, 0xce, 0x76, 0xdb,
    0x36, 0xd8, 0xf6, 0xc7, 0x9e, 0x38, 0xe1, 0xc7,
    0xe, 0x18,

    /* U+0078 "x" */
    0x61, 0x9c, 0xe3, 0x30, 0x68, 0x1c, 0x3, 0x1,
    0xe0, 0xfc, 0x33, 0x18, 0x6e, 0x1c,

    /* U+0079 "y" */
    0xc3, 0x67, 0x66, 0x34, 0x30, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+007A "z" */
    0xff, 0xf8, 0x70, 0xc1, 0x86, 0xc, 0x30, 0x61,
    0xff, 0xf8,

    /* U+007B "{" */
    0x39, 0xcc, 0x63, 0x73, 0x86, 0x31, 0xce,

    /* U+007C "|" */
    0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xce, 0x66, 0x63, 0x36, 0x6e, 0xe0,

    /* U+007E "~" */
    0xf0, 0xff, 0xf
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 75, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 66, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 103, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 156, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 224, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 50, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 55, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 63, .adv_w = 100, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 101, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 120, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 79, .adv_w = 144, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 86, .adv_w = 71, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 88, .adv_w = 85, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 90, .adv_w = 62, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 148, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 94, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 145, .box_w = 8, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 62, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 70, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 205, .adv_w = 144, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 214, .adv_w = 144, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 219, .adv_w = 144, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 228, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 193, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 118, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 196, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 58, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 152, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 230, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 200, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 145, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 206, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 231, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 145, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 601, .adv_w = 149, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 92, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 605, .adv_w = 193, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 118, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 198, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 58, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 152, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 230, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 755, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 200, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 145, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 206, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 843, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 231, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 911, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 921, .adv_w = 81, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 45, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 931, .adv_w = 82, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 937, .adv_w = 147, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 4}
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
const lv_font_t ui_font_LecturaS = {
#else
lv_font_t ui_font_LecturaS = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_LECTURAS*/

