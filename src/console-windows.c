/*
 * Copyright (C) 2010-2025 by Joseph A. Marrero. https://joemarrero.com/
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
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <wchar.h>
#include <ctype.h>
#include <wctype.h>
#include "xtd/string.h"
#include "xtd/time.h"
#include "xtd/console.h"

#ifdef _WIN32
#define snprintf _snprintf
#endif

void console_set_document(FILE* stream, const char* document)
{
    // nop
}

void console_set_working_directory(FILE* stream, const char* path)
{
    // nop
}

void console_color_4(FILE* stream, int color)
{
    // nop
}

void wconsole_fg_color_4(FILE* stream, int color)
{
    // nop
}

void console_fg_color_8(FILE* stream, int color)
{
    // nop
}

void wconsole_fg_color_8(FILE* stream, int color)
{
    // nop
}

void console_bg_color_8(FILE* stream, int color)
{
    // nop
}

void wconsole_bg_color_8(FILE* stream, int color)
{
    // nop
}

void console_fg_color_24(FILE* stream, unsigned char r, unsigned char g, unsigned char b)
{
    // nop
}

void console_bg_color_24(FILE* stream, unsigned char r, unsigned char g, unsigned char b)
{
    // nop
}

void console_reset_fg_color(FILE* stream)
{
    // nop
}

void console_reset_bg_color(FILE* stream)
{
    // nop
}


void console_bold_begin(FILE* stream)
{
    // nop
}

void console_bold_end(FILE* stream)
{
    // nop
}

void console_italic_begin(FILE* stream)
{
    // nop
}

void console_italic_end(FILE* stream)
{
    // nop
}

void wconsole_bold_begin(FILE* stream)
{
    // nop
}

void wconsole_bold_end(FILE* stream)
{
    // nop
}

void console_underline_begin(FILE* stream)
{
    // nop
}

void console_underline_end(FILE* stream)
{
    // nop
}

void console_strikethrough_begin(FILE* stream)
{
    // nop
}

void console_strikethrough_end(FILE* stream)
{
    // nop
}

void wconsole_underline_begin(FILE* stream)
{
    // nop
}

void wconsole_underline_end(FILE* stream)
{
    // nop
}

void console_reversed_begin(FILE* stream)
{
    // nop
}

void console_reversed_end(FILE* stream)
{
    // nop
}

void console_conceal_begin(FILE* stream)
{
    // nop
}

void console_conceal_end(FILE* stream)
{
    // nop
}

void console_blink_begin(FILE* stream)
{
    // nop
}

void console_blink_end(FILE* stream)
{
    // nop
}

void console_set_font(FILE* stream, int f)
{
    // nop
}

void wconsole_reversed_begin(FILE* stream)
{
    // nop
}

void wconsole_reversed_end(FILE* stream)
{
    // nop
}

void console_hide_cursor(FILE* stream)
{
    // nop
}

void wconsole_hide_cursor(FILE* stream)
{
    // nop
}

void console_show_cursor(FILE* stream)
{
    // nop
}

void wconsole_show_cursor(FILE* stream)
{
    // nop
}

void console_reset(FILE* stream)
{
    // nop
}

void wconsole_reset(FILE* stream)
{
    // nop
}

bool console_echo_enable(FILE* stream)
{
    // nop
    return false;
}

bool console_echo_disable(FILE* stream)
{
    // nop
    return false;
}

bool console_canonical_enable(FILE* stream)
{
    // nop
    return false;
}

bool console_canonical_disable(FILE* stream)
{
    // nop
    return false;
}

void console_save_position(FILE* stream)
{
    // nop
}

void console_restore_position(FILE* stream)
{
    // nop
}

void console_move_up(FILE* stream, int n)
{
    // nop
}

void console_move_down(FILE* stream, int n)
{
    // nop
}

void console_move_left(FILE* stream, int n)
{
    // nop
}

void console_move_right(FILE* stream, int n)
{
    // nop
}

void console_page_up(FILE* stream, int n)
{
    // nop
}

void console_page_down(FILE* stream, int n)
{
    // nop
}

void console_next_line(FILE* stream, int n)
{
    // nop
}

void console_prev_line(FILE* stream, int n)
{
    // nop
}

void console_set_column(FILE* stream, int x)
{
    // nop
}

void console_goto(FILE* stream, int x, int y)
{
    // nop
}

bool console_get_cursor_position(FILE* stream, int* x, int* y)
{
    // nop
    return false;
}

void console_clear_screen(FILE* stream, int type)
{
    // nop
}

void console_clear_line(FILE* stream, int type)
{
    // nop
}

bool console_size(FILE* stream, int* rows, int* cols)
{
    // nop
    return false;
}

bool console_set_size(FILE* stream, int rows, int cols)
{
    // nop
    return false;
}

void console_bar_graph(FILE* stream, int bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent)
{
    const int blocks = (bar_width * percent) / 100;

    for (int j = 0; j < bar_width; j++)
    {
        int color_idx = (color_count * j) / bar_width;
        if (j <= blocks)
        {
            if (bar_symbol == ' ')
            {
                console_bg_color_8(stream, colors[color_idx]);
            }
            else
            {
                console_fg_color_8(stream, colors[color_idx]);
            }
        }
        else
        {
            if (bar_symbol == ' ')
            {
                console_bg_color_8(stream, bkg_color);
            }
            else
            {
                console_fg_color_8(stream, bkg_color);
            }
        }
        fprintf(stream, "%c", bar_symbol);
    }
    console_reset(stream);
    fflush(stream);
}

static inline void __console_progress_indicator_ex(FILE* stream, const char* task, int progress_bar_width, char progress_bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent)
{
    // nop
    fflush(stream);
}

void console_progress_indicator_ex(FILE* stream, const char* task, int progress_bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, console_progress_fxn_t fxn, void* data)
{
    // nop
    fprintf(stream, "\n");
}

void console_progress_indicator(FILE* stream, const char* task, console_progress_indictor_style_t style, console_progress_fxn_t fxn, void* data)
{
    // nop
}

void console_text_fader_ex(FILE* stream, const char* text, const int* colors, size_t color_count, int millis)
{
    // nop

    console_reset(stream);
    console_show_cursor(stream);
    fflush(stream);
}

void console_text_fader(FILE* stream, console_text_fader_style_t style, const char* text)
{
    // nop
}

void console_text_faderf(FILE* stream, console_text_fader_style_t style, const char* format, ...)
{
    char fmtbuf[ 256 ];
    va_list args;
    va_start(args, format);
    vsnprintf(fmtbuf, sizeof(fmtbuf), format, args);
    fmtbuf[ sizeof(fmtbuf) - 1 ] = '\0';
    va_end(args);
    console_text_fader(stream, style, fmtbuf);
}

void console_print_divider(FILE* stream, const char* title)
{
    const char* empty = "";

    if (!title)
    {
        title = empty;
    }

    if (title)
    {
        char buffer[ 64 ] = { '\0' };
        size_t len = strlen(title);
        int half_len = len >> 1;
        int half_buffer = sizeof(buffer) >> 1;

        snprintf(buffer, sizeof(buffer), "%*s%*s", half_buffer + half_len, title, half_buffer - half_len, empty);

        for (size_t i = 0; i < sizeof(buffer) - 1; i++)
        {
            if (isspace(buffer[i]))
            {
                buffer[ i ] = '-';
            }
            else
            {
                break;
            }
        }

        for (size_t i = sizeof(buffer) - 1; ; i--)
        {
            if (isspace(buffer[i]) || buffer[i] == '\0')
            {
                buffer[ i ] = '-';
            }
            else
            {
                break;
            }
        }

        buffer[ sizeof(buffer) - 1 ] = '\0';

        fprintf(stream, "--%s--\n", buffer);
    }
}

bool console_command_prompt(char* command_buf, size_t command_buf_size, const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data)
{
    bool not_quiting = true;

    console_fg_color_8(stdout, prompt_color);
    fputs(prompt, stdout);
    console_reset(stdout);

    if (fgets(command_buf, command_buf_size, stdin))
    {
        string_trim(command_buf, " \t\r\n");
        not_quiting = on_cmd(command_buf, data);
    }

    return not_quiting;
}

void console_command_prompt_loop(const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data)
{
    bool quiting = false;
    char command[ 256 ];

    while (!quiting)
    {
        if (!console_command_prompt(command, sizeof(command), prompt, prompt_color, on_cmd, data))
        {
            quiting = true;
        }
    }
}


// requires calling setlocale(LC_ALL, "")
void console_curved_box(int x, int y, int w, int h)
{
}

