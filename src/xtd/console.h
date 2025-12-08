/*
 * Copyright (C) 2016-2025 by Joseph A. Marrero. https://joemarrero.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef _XTD_CONSOLE_H_
#define _XTD_CONSOLE_H_

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
# include <stdint.h>
#else
# error "Need a C99 compiler."
#endif

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201121L)) // C11
# include <stdnoreturn.h>
#else
# ifndef noreturn
#  define noreturn
# endif
#endif

/*
 * Console
 */

typedef bool (*console_progress_fxn_t)       (int* percent, void* data);
typedef bool (*console_handle_command_fxn_t) (const char* command, void* data);
typedef enum console_progress_indictor_style {
    PROGRESS_INDICATOR_STYLE_BLUE,
    PROGRESS_INDICATOR_STYLE_FADE,
    PROGRESS_INDICATOR_STYLE_INTENSITY,
} console_progress_indictor_style_t;

typedef enum console_text_fader_style {
    TEXT_FADER_TO_WHITE,
    TEXT_FADER_TO_BLACK,
    TEXT_FADER_TO_YELLOW,
    TEXT_FADER_TO_ORANGE,
    TEXT_FADER_TO_GREEN,
    TEXT_FADER_TO_BLUE,
    TEXT_FADER_TO_RED,
    TEXT_FADER_BLUE_BEEP,
} console_text_fader_style_t;

#define CONSOLE_CLEAR_CURSOR_TO_END     0
#define CONSOLE_CLEAR_CURSOR_TO_START   1
#define CONSOLE_CLEAR_ALL               2

#define CONSOLE_FONT_0     10
#define CONSOLE_FONT_1     11
#define CONSOLE_FONT_2     12
#define CONSOLE_FONT_3     13

void console_set_document          (FILE* stream, const char* document); /* macos x only */
void console_set_working_directory (FILE* stream, const char* path); /* macos x only */

void console_color_4               (FILE* stream, int color);
void console_fg_color_8            (FILE* stream, int color);
void console_bg_color_8            (FILE* stream, int color);
void console_fg_color_24           (FILE* stream, unsigned char r, unsigned char g, unsigned char b);
void console_bg_color_24           (FILE* stream, unsigned char r, unsigned char g, unsigned char b);
void console_reset_fg_color        (FILE* stream);
void console_reset_bg_color        (FILE* stream);
void console_bold_begin            (FILE* stream);
void console_bold_end              (FILE* stream);
void console_italic_begin          (FILE* stream);  /* Not widely supported */
void console_italic_end            (FILE* stream);  /* Not widely supported */
void console_underline_begin       (FILE* stream);
void console_underline_end         (FILE* stream);
void console_strikethrough_begin   (FILE* stream);
void console_strikethrough_end     (FILE* stream);
void console_reversed_begin        (FILE* stream);
void console_reversed_end          (FILE* stream);
void console_conceal_begin         (FILE* stream);
void console_conceal_end           (FILE* stream);
void console_blink_begin           (FILE* stream);
void console_blink_end             (FILE* stream);
void console_set_font              (FILE* stream, int f); /* Not widely supported */
void console_reset                 (FILE* stream);
bool console_echo_enable           (FILE* stream);
bool console_echo_disable          (FILE* stream);
bool console_canonical_enable      (FILE* stream);
bool console_canonical_disable     (FILE* stream);

void console_hide_cursor           (FILE* stream);
void console_show_cursor           (FILE* stream);
void console_save_position         (FILE* stream);
void console_restore_position      (FILE* stream);
void console_move_up               (FILE* stream, int n);
void console_move_down             (FILE* stream, int n);
void console_move_left             (FILE* stream, int n);
void console_move_right            (FILE* stream, int n);
void console_page_up               (FILE* stream, int n);
void console_page_down             (FILE* stream, int n);
void console_next_line             (FILE* stream, int n);
void console_prev_line             (FILE* stream, int n);
void console_set_column            (FILE* stream, int x);
void console_goto                  (FILE* stream, int x, int y);
bool console_get_cursor_position   (FILE* stream, int* x, int* y);
void console_clear_screen          (FILE* stream, int type);
void console_clear_line            (FILE* stream, int type);
bool console_size                  (FILE* stream, int* rows, int* cols);
bool console_set_size              (FILE* stream, int rows, int cols);
void console_bar_graph             (FILE* stream, int bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent);
void console_progress_indicator_ex (FILE* stream, const char* task, int progress_bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, console_progress_fxn_t fxn, void* data);
void console_progress_indicator    (FILE* stream, const char* task, console_progress_indictor_style_t style, console_progress_fxn_t fxn, void* data);
void console_text_fader_ex         (FILE* stream, const char* text, const int* colors, size_t color_count, int millis);
void console_text_fader            (FILE* stream, console_text_fader_style_t style, const char* text);
void console_text_faderf           (FILE* stream, console_text_fader_style_t style, const char* format, ...);
void console_print_divider         (FILE* stream, const char* title);

bool console_command_prompt      (char* command_buf, size_t command_buf_size, const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data);
void console_command_prompt_loop (const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data);


void wconsole_fg_color_4        (FILE* stream, int color);
void wconsole_fg_color_8        (FILE* stream, int color);
void wconsole_bg_color_8        (FILE* stream, int color);
void wconsole_bold_begin        (FILE* stream);
void wconsole_bold_end          (FILE* stream);
void wconsole_underline_begin   (FILE* stream);
void wconsole_underline_end     (FILE* stream);
void wconsole_reversed_begin    (FILE* stream);
void wconsole_reversed_end      (FILE* stream);
void wconsole_hide_cursor       (FILE* stream);
void wconsole_show_cursor       (FILE* stream);
void wconsole_reset             (FILE* stream);


#define console_clear_screen_to_end(stream)    console_clear_screen(stream, CONSOLE_CLEAR_CURSOR_TO_END) // clears from cursor to end of screen
#define console_clear_screen_from_beg(stream)  console_clear_screen(stream, CONSOLE_CLEAR_CURSOR_TO_START) // clears from cursor to start of screen
#define console_clear_screen_all(stream)       console_clear_screen(stream, CONSOLE_CLEAR_ALL) // clears whole screen
#define console_clear_line_to_end(stream)      console_clear_line(stream, CONSOLE_CLEAR_CURSOR_TO_END) // from cursor to end of line
#define console_clear_line_from_beg(stream)    console_clear_line(stream, CONSOLE_CLEAR_CURSOR_TO_START) // from cursor to start of line
#define console_clear_line_all(stream)         console_clear_line(stream, CONSOLE_CLEAR_ALL) // clears whole line


#define CONSOLE_FG_COLOR4_BLACK             30
#define CONSOLE_FG_COLOR4_RED               31
#define CONSOLE_FG_COLOR4_GREEN             32
#define CONSOLE_FG_COLOR4_YELLOW            33
#define CONSOLE_FG_COLOR4_BLUE              34
#define CONSOLE_FG_COLOR4_MAGENTA           35
#define CONSOLE_FG_COLOR4_CYAN              36
#define CONSOLE_FG_COLOR4_WHITE             37
#define CONSOLE_FG_COLOR4_BRIGHT_BLACK      90
#define CONSOLE_FG_COLOR4_BRIGHT_RED        91
#define CONSOLE_FG_COLOR4_BRIGHT_GREEN      92
#define CONSOLE_FG_COLOR4_BRIGHT_YELLOW     93
#define CONSOLE_FG_COLOR4_BRIGHT_BLUE       94
#define CONSOLE_FG_COLOR4_BRIGHT_MAGENTA    95
#define CONSOLE_FG_COLOR4_BRIGHT_CYAN       96
#define CONSOLE_FG_COLOR4_BRIGHT_WHITE      97

#define CONSOLE_BG_COLOR4_BLACK             40
#define CONSOLE_BG_COLOR4_RED               41
#define CONSOLE_BG_COLOR4_GREEN             42
#define CONSOLE_BG_COLOR4_YELLOW            43
#define CONSOLE_BG_COLOR4_BLUE              44
#define CONSOLE_BG_COLOR4_MAGENTA           45
#define CONSOLE_BG_COLOR4_CYAN              46
#define CONSOLE_BG_COLOR4_WHITE             47
#define CONSOLE_BG_COLOR4_BRIGHT_BLACK      100
#define CONSOLE_BG_COLOR4_BRIGHT_RED        101
#define CONSOLE_BG_COLOR4_BRIGHT_GREEN      102
#define CONSOLE_BG_COLOR4_BRIGHT_YELLOW     103
#define CONSOLE_BG_COLOR4_BRIGHT_BLUE       104
#define CONSOLE_BG_COLOR4_BRIGHT_MAGENTA    105
#define CONSOLE_BG_COLOR4_BRIGHT_CYAN       106
#define CONSOLE_BG_COLOR4_BRIGHT_WHITE      107

#define CONSOLE_COLOR8_BLACK           0x00
#define CONSOLE_COLOR8_RED             0x01
#define CONSOLE_COLOR8_GREEN           0x02
#define CONSOLE_COLOR8_YELLOW          0x03
#define CONSOLE_COLOR8_BLUE            0x04
#define CONSOLE_COLOR8_MAGENTA         0x05
#define CONSOLE_COLOR8_CYAN            0x06
#define CONSOLE_COLOR8_WHITE           0x07

#define CONSOLE_COLOR8_BRIGHT_BLACK    0x08
#define CONSOLE_COLOR8_BRIGHT_RED      0x09
#define CONSOLE_COLOR8_BRIGHT_GREEN    0x0a
#define CONSOLE_COLOR8_BRIGHT_YELLOW   0x0b
#define CONSOLE_COLOR8_BRIGHT_BLUE     0x0c
#define CONSOLE_COLOR8_BRIGHT_MAGENTA  0x0d
#define CONSOLE_COLOR8_BRIGHT_CYAN     0x0e
#define CONSOLE_COLOR8_BRIGHT_WHITE    0x0f

#define CONSOLE_COLOR8_RGB(r, g, b)    (16 + 36 * (r) + 6 * (g) + (b)) /* r in [0, 5], g in [0, 5], b in [0, 5] */

#define CONSOLE_COLOR8_GREY_00         0xe8  /* darker */
#define CONSOLE_COLOR8_GREY_01         0xe9
#define CONSOLE_COLOR8_GREY_02         0xea
#define CONSOLE_COLOR8_GREY_03         0xeb
#define CONSOLE_COLOR8_GREY_04         0xec
#define CONSOLE_COLOR8_GREY_05         0xed
#define CONSOLE_COLOR8_GREY_06         0xee
#define CONSOLE_COLOR8_GREY_07         0xef
#define CONSOLE_COLOR8_GREY_08         0xf0
#define CONSOLE_COLOR8_GREY_09         0xf1
#define CONSOLE_COLOR8_GREY_10         0xf2
#define CONSOLE_COLOR8_GREY_11         0xf3
#define CONSOLE_COLOR8_GREY_12         0xf4
#define CONSOLE_COLOR8_GREY_13         0xf5
#define CONSOLE_COLOR8_GREY_14         0xf6
#define CONSOLE_COLOR8_GREY_15         0xf7
#define CONSOLE_COLOR8_GREY_16         0xf8
#define CONSOLE_COLOR8_GREY_17         0xf9
#define CONSOLE_COLOR8_GREY_18         0xfa
#define CONSOLE_COLOR8_GREY_19         0xfb
#define CONSOLE_COLOR8_GREY_20         0xfc
#define CONSOLE_COLOR8_GREY_21         0xfd
#define CONSOLE_COLOR8_GREY_22         0xfe
#define CONSOLE_COLOR8_GREY_23         0xff /* lighter */


#define CONSOLE_CURVED_BOX_TLCORNER    L'\x256d' // ╭
#define CONSOLE_CURVED_BOX_TRCORNER    L'\x256e' // ╮
#define CONSOLE_CURVED_BOX_BRCORNER    L'\x256f' // ╯
#define CONSOLE_CURVED_BOX_BLCORNER    L'\x2570' // ╰
#define CONSOLE_CURVED_BOX_HLINE       L'\x2500' // ╶
#define CONSOLE_CURVED_BOX_VLINE       L'\x2502' // ╷

void console_curved_box(int x, int y, int width, int height);


#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
    using ::console_color_4;
    using ::console_fg_color_8;
    using ::console_bg_color_8;
    using ::console_bold;
    using ::console_underline;
    using ::console_reversed;
    using ::console_hide_cursor;
    using ::console_show_cursor;
    using ::console_reset;
    using ::console_save_position;
    using ::console_restore_position;
    using ::console_move_up;
    using ::console_move_down;
    using ::console_move_left;
    using ::console_move_right;
    using ::console_bar_graph;
    using ::console_progress_indicator_ex;
    using ::console_progress_indicator;
    using ::console_next_line;
    using ::console_prev_line;
    using ::console_set_column;
    using ::console_goto;
    using ::console_clear_screen;
    using ::console_clear_line;
    using ::console_text_fader_ex;
    using ::console_text_fader;
    using ::console_print_divider;
    using ::console_command_prompt;
    using ::console_command_prompt_loop;
} /* namespace */
#endif
#endif /* _XTD_CONSOLE_H_ */

