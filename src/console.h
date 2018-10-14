/*
 * Copyright (C) 2016 by Joseph A. Marrero. http://www.manvscode.com/
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
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

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

typedef bool (*console_progress_fxn_t)       ( int* percent, void* data );
typedef bool (*console_handle_command_fxn_t) ( const char* command, void* data );
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

void console_fg_color_8            ( FILE* stream, int color );
void console_fg_bright_color_8     ( FILE* stream, int color );
void console_fg_color_256          ( FILE* stream, int color );
void console_bg_color_256          ( FILE* stream, int color );
void console_bold                  ( FILE* stream );
void console_underline             ( FILE* stream );
void console_reversed              ( FILE* stream );
void console_hide_cursor           ( FILE* stream );
void console_show_cursor           ( FILE* stream );
void console_reset                 ( FILE* stream );
void console_save_position         ( FILE* stream );
void console_restore_position      ( FILE* stream );
void console_move_up               ( FILE* stream, int n );
void console_move_down             ( FILE* stream, int n );
void console_move_left             ( FILE* stream, int n );
void console_move_right            ( FILE* stream, int n );
void console_bar_graph             ( FILE* stream, int bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent );
void console_progress_indicator_ex ( FILE* stream, const char* task, int progress_bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, console_progress_fxn_t fxn, void* data );
void console_progress_indicator    ( FILE* stream, const char* task, console_progress_indictor_style_t style, console_progress_fxn_t fxn, void* data );
void console_next_line             ( FILE* stream, int n );
void console_prev_line             ( FILE* stream, int n );
void console_set_column            ( FILE* stream, int x );
void console_goto                  ( FILE* stream, int x, int y );
void console_clear_screen          ( FILE* stream, int type );
void console_clear_line            ( FILE* stream, int type );
void console_text_fader_ex         ( FILE* stream, const char* text, const int* colors, size_t color_count, int millis );
void console_text_fader            ( FILE* stream, console_text_fader_style_t style, const char* text );
void console_text_faderf           ( FILE* stream, console_text_fader_style_t style, const char* format, ... );
void console_print_divider         ( FILE* stream, const char* title );

bool console_command_prompt               ( char* command_buf, size_t command_buf_size, const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data );
noreturn void console_command_prompt_loop ( const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data );


void wconsole_fg_color_8        ( FILE* stream, int color );
void wconsole_fg_bright_color_8 ( FILE* stream, int color );
void wconsole_fg_color_256      ( FILE* stream, int color );
void wconsole_bg_color_256      ( FILE* stream, int color );
void wconsole_bold              ( FILE* stream );
void wconsole_underline         ( FILE* stream );
void wconsole_reversed          ( FILE* stream );
void wconsole_hide_cursor       ( FILE* stream );
void wconsole_show_cursor       ( FILE* stream );
void wconsole_reset             ( FILE* stream );


#define console_clear_screen_to_end(stream)    console_clear_screen( stream, 0 ) // clears from cursor to end of screen
#define console_clear_screen_from_beg(stream)  console_clear_screen( stream, 1 ) // clears from cursor to start of screen
#define console_clear_screen_all(stream)       console_clear_screen( stream, 2 ) // clears whole screen
#define console_clear_line_to_end(stream)      console_clear_line( stream, 0 ) // from cursor to end of line
#define console_clear_line_from_beg(stream)    console_clear_line( stream, 1 ) // from cursor to start of line
#define console_clear_line_all(stream)         console_clear_line( stream, 2 ) // clears whole line


#define CONSOLE_COLOR8_BLACK             30
#define CONSOLE_COLOR8_RED               31
#define CONSOLE_COLOR8_GREEN             32
#define CONSOLE_COLOR8_YELLOW            33
#define CONSOLE_COLOR8_BLUE              34
#define CONSOLE_COLOR8_MAGENTA           35
#define CONSOLE_COLOR8_CYAN              36
#define CONSOLE_COLOR8_WHITE             37

#define CONSOLE_COLOR256_BLACK           0x00
#define CONSOLE_COLOR256_RED             0x01
#define CONSOLE_COLOR256_GREEN           0x02
#define CONSOLE_COLOR256_YELLOW          0x03
#define CONSOLE_COLOR256_BLUE            0x04
#define CONSOLE_COLOR256_MAGENTA         0x05
#define CONSOLE_COLOR256_CYAN            0x06
#define CONSOLE_COLOR256_WHITE           0x07
#define CONSOLE_COLOR256_BRIGHT_BLACK    0x08
#define CONSOLE_COLOR256_BRIGHT_RED      0x09
#define CONSOLE_COLOR256_BRIGHT_GREEN    0x0a
#define CONSOLE_COLOR256_BRIGHT_YELLOW   0x0b
#define CONSOLE_COLOR256_BRIGHT_BLUE     0x0c
#define CONSOLE_COLOR256_BRIGHT_MAGENTA  0x0d
#define CONSOLE_COLOR256_BRIGHT_CYAN     0x0e
#define CONSOLE_COLOR256_BRIGHT_WHITE    0x0f
#define CONSOLE_COLOR256_GREY_00         0xe8
#define CONSOLE_COLOR256_GREY_01         0xe9
#define CONSOLE_COLOR256_GREY_02         0xea
#define CONSOLE_COLOR256_GREY_03         0xeb
#define CONSOLE_COLOR256_GREY_04         0xec
#define CONSOLE_COLOR256_GREY_05         0xed
#define CONSOLE_COLOR256_GREY_06         0xee
#define CONSOLE_COLOR256_GREY_07         0xef
#define CONSOLE_COLOR256_GREY_08         0xf0
#define CONSOLE_COLOR256_GREY_09         0xf1
#define CONSOLE_COLOR256_GREY_10         0xf2
#define CONSOLE_COLOR256_GREY_11         0xf3
#define CONSOLE_COLOR256_GREY_12         0xf4
#define CONSOLE_COLOR256_GREY_13         0xf5
#define CONSOLE_COLOR256_GREY_14         0xf6
#define CONSOLE_COLOR256_GREY_15         0xf7
#define CONSOLE_COLOR256_GREY_16         0xf8
#define CONSOLE_COLOR256_GREY_17         0xf9
#define CONSOLE_COLOR256_GREY_18         0xfa
#define CONSOLE_COLOR256_GREY_19         0xfb
#define CONSOLE_COLOR256_GREY_20         0xfc
#define CONSOLE_COLOR256_GREY_21         0xfd
#define CONSOLE_COLOR256_GREY_22         0xfe
#define CONSOLE_COLOR256_GREY_23         0xff



#ifdef __cplusplus
} /* extern "C" */
namespace utility {
    using ::console_fg_color_8;
    using ::console_fg_bright_color_8;
    using ::console_fg_color_256;
    using ::console_bg_color_256;
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
#endif /* _CONSOLE_H_ */

