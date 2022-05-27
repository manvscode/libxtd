/*
 * Copyright (C) 2010-2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#include <sys/ioctl.h>
#include <sys/termios.h>
#include <unistd.h>
#include "xtd/string.h"
#include "xtd/time.h"
#include "xtd/console.h"

#ifdef _WIN32
#define snprintf _snprintf
#endif

const int COLORS_BLUE_BEEP[] = {
	0x19, 0x1a, 0x1b, 0x20, 0x21,
	0x26, 0x27, 0x07, 0x0f
};
const int COLORS_FADER_TO_RED[] = {
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8,
	0xc9, 0xd4, 0xd5, 0x07, 0x0f
};
const int COLORS_FADER_TO_BLUE[] = {
	0x15, 0x14, 0x13, 0x12, 0x11,
	0x10
};
const int COLORS_FADER_TO_GREEN[] = {
	0x52, 0x53, 0x54, 0x55, 0x56,
	0x57
};
const int COLORS_FADER_TO_ORANGE[] = {
	0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd9, 0xd8, 0xd7, 0xd6,
	0x07, 0x0f
};
const int COLORS_FADER_TO_YELLOW[] = {
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6,
	0xe7
};
const int COLORS_FADER_TO_BLACK[] = {
	0x00, 0x10, 0xea, 0xeb, 0xec,
	0xed, 0xee, 0xef, 0xf0, 0xf1,
	0xf2, 0xf3, 0xf4, 0xf5, 0xf6,
	0xf7, 0xf8, 0xf9, 0xfa, 0xfb,
	0xfc, 0xfd, 0xfe, 0xff
};
const int COLORS_FADER_TO_WHITE[] = {
	0xff, 0xfe, 0xfd, 0xfc, 0xfb,
	0xfa, 0xf9, 0xf8, 0xf7, 0xf6,
	0xf5, 0xf4, 0xf3, 0xf2, 0xf1
};
const int COLORS_PROGRESS_FADE[] = {
	0xea, 0xeb, 0xec, 0xed, 0xee,
	0xef, 0xf0, 0xf1, 0xf2, 0xf3,
	0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa, 0xfb, 0xfc, 0xfd,
	0xfe, 0xff
};
const int COLORS_PROGRESS_INTENSITY[] = {
	0x02, 0x22, 0x28, 0x9a, 0xe2,
	0xdc, 0xd6, 0xd0, 0xc4
};
const int COLORS_PROGRESS_BLUE[] = { 0x15 };

void console_set_document( FILE* stream, const char* document )
{
    fprintf( stream, "\033]6;%s\007", document );
}

void console_set_working_directory( FILE* stream, const char* path )
{
    fprintf( stream, "\033]7;%s\007", path );
}

void console_color_4( FILE* stream, int color )
{
	fprintf( stream, "\033[%dm", color );
}

void wconsole_fg_color_4( FILE* stream, int color )
{
	fwprintf( stream, L"\033[%dm", color );
}

//void console_fg_bright_color_4( FILE* stream, int color )
//{
	//fprintf( stream, "\033[%d;1m", color );
//}

//void wconsole_fg_bright_color_4( FILE* stream, int color )
//{
	//fwprintf( stream, L"\033[%d;1m", color );
//}

void console_fg_color_8( FILE* stream, int color )
{
	fprintf( stream, "\033[38;5;%dm", color );
}

void wconsole_fg_color_8( FILE* stream, int color )
{
	fwprintf( stream, L"\033[38;5;%dm", color );
}

void console_bg_color_8( FILE* stream, int color )
{
	fprintf( stream, "\033[48;5;%dm", color );
}

void wconsole_bg_color_8( FILE* stream, int color )
{
	fwprintf( stream, L"\033[48;5;%dm", color );
}

void console_fg_color_24( FILE* stream, unsigned char r, unsigned char g, unsigned char b )
{
	fprintf( stream, "\033[38;2;%d;%d;%dm", (int) r, (int) g, (int) b ); // TODO
}

void console_bg_color_24( FILE* stream, unsigned char r, unsigned char g, unsigned char b )
{
	fprintf( stream, "\033[48;2;%d;%d;%dm", (int) r, (int) g, (int) b ); // TODO
}

void console_reset_fg_color( FILE* stream )
{
	fprintf( stream, "\033[39m" );
}

void console_reset_bg_color( FILE* stream )
{
	fprintf( stream, "\033[49m" );
}


void console_bold_begin( FILE* stream )
{
	fprintf( stream, "\033[1m" );
}

void console_bold_end( FILE* stream )
{
	fprintf( stream, "\033[21m" );
}

void console_italic_begin( FILE* stream )
{
	fprintf( stream, "\033[3m" );
}

void console_italic_end( FILE* stream )
{
	fprintf( stream, "\033[23m" );
}

void wconsole_bold_begin( FILE* stream )
{
	fwprintf( stream, L"\033[1m" );
}

void wconsole_bold_end( FILE* stream )
{
	fwprintf( stream, L"\033[21m" );
}

void console_underline_begin( FILE* stream )
{
	fprintf( stream, "\033[4m" );
}

void console_underline_end( FILE* stream )
{
	fprintf( stream, "\033[24m" );
}

void console_strikethrough_begin( FILE* stream )
{
	fprintf( stream, "\033[9m" );
}

void console_strikethrough_end( FILE* stream )
{
	fprintf( stream, "\033[29m" );
}

void wconsole_underline_begin( FILE* stream )
{
	fwprintf( stream, L"\033[4m" );
}

void wconsole_underline_end( FILE* stream )
{
	fwprintf( stream, L"\033[24m" );
}

void console_reversed_begin( FILE* stream )
{
	fprintf( stream, "\033[7m" );
}

void console_reversed_end( FILE* stream )
{
	fprintf( stream, "\033[27m" );
}

void console_conceal_begin( FILE* stream )
{
	fprintf( stream, "\033[8m" );
}

void console_conceal_end( FILE* stream )
{
	fprintf( stream, "\033[28m" );
}

void console_blink_begin( FILE* stream )
{
	//fprintf( stream, "\033[%dm", fast ? 6 : 5 );
	fprintf( stream, "\033[5m" );
}

void console_blink_end( FILE* stream )
{
	//fprintf( stream, "\033[%dm", fast ? 6 : 5 );
	fprintf( stream, "\033[25m" );
}

void console_set_font( FILE* stream, int f )
{
	fprintf( stream, "\033[%dm", f );
}

void wconsole_reversed_begin( FILE* stream )
{
	fwprintf( stream, L"\033[7m" );
}

void wconsole_reversed_end( FILE* stream )
{
	fwprintf( stream, L"\033[27m" );
}

void console_hide_cursor( FILE* stream )
{
	fprintf( stream, "\033[?25l" );
}

void wconsole_hide_cursor( FILE* stream )
{
	fwprintf( stream, L"\033[?25l" );
}

void console_show_cursor( FILE* stream )
{
	fprintf( stream, "\033[?25h" );
}

void wconsole_show_cursor( FILE* stream )
{
	fwprintf( stream, L"\033[?25h" );
}

void console_reset( FILE* stream )
{
	fprintf( stream, "\033[0m" );
}

void wconsole_reset( FILE* stream )
{
	fwprintf( stream, L"\033[0m" );
}

bool console_echo_enable( FILE* stream )
{
	bool result = false;
	struct termios tbuf;
	int fd = fileno(stream);
#if 0
	if( fd >= 0 && !ioctl(fd, TCGETS, &tbuf) )
	{
		tbuf.c_lflag |= ECHO;

		if( !ioctl(fd, TCSETS, &tbuf) )
		{
			result = true;
		}
	}
#else
	if( fd >= 0 && !tcgetattr(fd, &tbuf) )
	{
		tbuf.c_lflag |= ECHO;

		if( !tcsetattr(fd, TCSANOW, &tbuf) )
		{
			result = true;
		}
	}
#endif

	return result;

}

bool console_echo_disable( FILE* stream )
{
	bool result = false;
	struct termios tbuf;
	int fd = fileno(stream);
#if 0
	if( fd >= 0 && !ioctl(fd, TCGETS, &tbuf) )
	{
		tbuf.c_lflag &= ~ECHO;

		if( !ioctl(fd, TCSETS, &tbuf) )
		{
			result = true;
		}
	}
#else
	if( fd >= 0 && !tcgetattr(fd, &tbuf) )
	{
		tbuf.c_lflag &= ~ECHO;

		if( !tcsetattr(fd, TCSANOW, &tbuf) )
		{
			result = true;
		}
	}
#endif

	return result;
}

bool console_canonical_enable( FILE* stream )
{
	bool result = false;
	struct termios tbuf;
	int fd = fileno(stream);
#if 0
	if( fd >= 0 && !ioctl(fd, TCGETS, &tbuf) )
	{
		tbuf.c_lflag |= ICANON;

		if( !ioctl(fd, TCSETS, &tbuf) )
		{
			result = true;
		}
	}
#else
	if( fd >= 0 && !tcgetattr(fd, &tbuf) )
	{
		tbuf.c_lflag |= ICANON;

		if( !tcsetattr(fd, TCSANOW, &tbuf) )
		{
			result = true;
		}
	}
#endif

	return result;
}

bool console_canonical_disable( FILE* stream )
{
	bool result = false;
	struct termios tbuf;
	int fd = fileno(stream);
#if 0
	if( fd >= 0 && !ioctl(fd, TCGETS, &tbuf) )
	{
		tbuf.c_lflag &= ~ICANON;

		if( !ioctl(fd, TCSETS, &tbuf) )
		{
			result = true;
		}
	}
#else
	if( fd >= 0 && !tcgetattr(fd, &tbuf) )
	{
		tbuf.c_lflag &= ~ICANON;

		if( !tcsetattr(fd, TCSANOW, &tbuf) )
		{
			result = true;
		}
	}
#endif

	return result;
}

void console_save_position( FILE* stream )
{
	fprintf( stream, "\033[s" );
}

void console_restore_position( FILE* stream )
{
	fprintf( stream, "\033[u" );
}

void console_move_up( FILE* stream, int n )
{
	fprintf( stream, "\033[%dA", n );
}

void console_move_down( FILE* stream, int n )
{
	fprintf( stream, "\033[%dB", n );
}

void console_move_left( FILE* stream, int n )
{
	fprintf( stream, "\033[%dD", n );
}

void console_move_right( FILE* stream, int n )
{
	fprintf( stream, "\033[%dC", n );
}

void console_page_up( FILE* stream, int n )
{
	fprintf( stream, "\033[%dS", n );
}

void console_page_down( FILE* stream, int n )
{
	fprintf( stream, "\033[%dT", n );
}

void console_next_line( FILE* stream, int n )
{
	fprintf( stream, "\033[%dE", n );
}

void console_prev_line( FILE* stream, int n )
{
	fprintf( stream, "\033[%dF", n );
}

void console_set_column( FILE* stream, int x )
{
	fprintf( stream, "\033[%dG", x );
}

void console_goto( FILE* stream, int x, int y )
{
	fprintf( stream, "\033[%d;%dH", y, x );
	//fprintf( stream, "\033[%d;%df", y, x ); // horizontal vertical position
}

bool console_get_cursor_position( FILE* stream, int* x, int* y )
{
	console_echo_disable(stdout);
	fprintf( stream, "\033[6n");
	fflush( stream );
	int result = fscanf( stdin, "\033[%d;%dR", y, x );
	console_echo_enable(stdout);
	return result == 2;
}

void console_clear_screen( FILE* stream, int type )
{
	fprintf( stream, "\033[%dJ", type );
}

void console_clear_line( FILE* stream, int type )
{
	fprintf( stream, "\033[%dK", type );
}

bool console_size( FILE* stream, int* rows, int* cols )
{
	struct winsize w;
	int fd = fileno(stream);
	if( fd >= 0 && !ioctl(fd, TIOCGWINSZ, &w) )
	{
		*rows = w.ws_row;
		*cols = w.ws_col;
		return true;
	}

	return false;
}

bool console_set_size( FILE* stream, int rows, int cols )
{
	struct winsize w = (struct winsize) {
		.ws_row = rows,
		.ws_col = cols,
	};
	int fd = fileno(stream);
	return fd >= 0 && !ioctl(fd, TIOCSWINSZ, &w);
}

void console_bar_graph( FILE* stream, int bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent )
{
	const int blocks = (bar_width * percent) / 100;

	for( int j = 0; j < bar_width; j++ )
	{
		int color_idx = (color_count * j) / bar_width;
		if( j <= blocks )
		{
			if( bar_symbol == ' ' )
			{
				console_bg_color_8( stream, colors[color_idx] );
			}
			else
			{
				console_fg_color_8( stream, colors[color_idx] );
			}
		}
		else
		{
			if( bar_symbol == ' ' )
			{
				console_bg_color_8( stream, bkg_color );
			}
			else
			{
				console_fg_color_8( stream, bkg_color );
			}
		}
		fprintf( stream, "%c", bar_symbol );
	}
	console_reset( stream );
	fflush( stream );
}

static inline void __console_progress_indicator_ex( FILE* stream, const char* task, int progress_bar_width, char progress_bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent )
{

#if 0
	fprintf( stream, "%s[", console_move_left(1000) );
#else
	//console_clear_line_all( stream );
#endif

#if __apple__
    /* Mac OS X does not support save/restore */
	console_set_column( stream, 0 );
#else
	console_save_position(stream);
#endif

	console_bar_graph( stream, progress_bar_width, progress_bar_symbol, colors, color_count, bkg_color, percent );
	fprintf( stream, " [%3d%%] %s", percent, task );
#if __apple__
    /* Mac OS X does not support save/restore */
#else
	console_restore_position(stream);
#endif
	fflush( stream );
}

void console_progress_indicator_ex( FILE* stream, const char* task, int progress_bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, console_progress_fxn_t fxn, void* data )
{
	bool is_progressing = true;
	for( int percent = 0; is_progressing && percent < 100; is_progressing = fxn( &percent, data ) )
	{
		__console_progress_indicator_ex( stream, task, progress_bar_width, bar_symbol, colors, color_count, bkg_color, percent );
	}

	if( is_progressing )
	{
		__console_progress_indicator_ex( stream, task, progress_bar_width, bar_symbol, colors, color_count, bkg_color, 100 );
	}
	fprintf( stream, "\n" );
}

void console_progress_indicator( FILE* stream, const char* task, console_progress_indictor_style_t style, console_progress_fxn_t fxn, void* data )
{
	const char progress_bar_symbol = ' ';
	const int progress_bar_width = 24;
	size_t color_count;
	const int* colors;
	int bkg_color;

	switch( style )
	{
		case PROGRESS_INDICATOR_STYLE_FADE:
		{
			colors      = COLORS_PROGRESS_FADE;
			color_count = sizeof(COLORS_PROGRESS_FADE) / sizeof(COLORS_PROGRESS_FADE[0]);
			bkg_color   = 0xe9;
			break;
		}
		case PROGRESS_INDICATOR_STYLE_INTENSITY:
		{
			colors      = COLORS_PROGRESS_INTENSITY;
			color_count = sizeof(COLORS_PROGRESS_INTENSITY) / sizeof(COLORS_PROGRESS_INTENSITY[0]);
			bkg_color   = 0xeb;
			break;
		}
		case PROGRESS_INDICATOR_STYLE_BLUE:
		default: /* fall through */
		{
			colors      = COLORS_PROGRESS_BLUE;
			color_count = sizeof(COLORS_PROGRESS_BLUE) / sizeof(COLORS_PROGRESS_BLUE[0]);
			bkg_color   = 0x11;
			break;
		}
	}

	console_progress_indicator_ex( stream, task, progress_bar_width, progress_bar_symbol, colors, color_count, bkg_color, fxn, data );
}

void console_text_fader_ex( FILE* stream, const char* text, const int* colors, size_t color_count, int millis )
{
	size_t len = strlen(text);

	console_hide_cursor( stream );
#if __apple__
    /* Mac OS X does not support save/restore */
#else
	console_save_position(stream);
#endif

	/*
	 * Start printing each character starting with the initial fade
	 * color up the color_count chars. This gives the illusion of the
	 * initial characters fading in.
	 */
	for( size_t i = 0, k = 0; k < color_count && i < len; i++, k++ )
	{
		console_fg_color_8( stream, colors[k] );
		fprintf( stream, "%c", text[ i ] );
		fflush( stream );

		time_msleep( millis );
	}

	/*
	 * If we have a string length greater than the color count,
	 * then we have to do some extra work. The characters less
	 * than the color count should be solid at this point, and
	 * the successive characters need to be faded in.
	 */
	if( len > color_count )
	{
		for( size_t j = color_count; j < len; j++ )
		{
			console_move_left( stream, j );
#if __apple__
    /* Mac OS X does not support save/restore */
#else
			console_restore_position(stream);
#endif

			/*
			 * Now we print all characters up the the jth character
			 * as the initial color (i.e. at index 0).
			 */
			for( size_t i = 0; j > color_count && i < j - color_count; i++ )
			{
				console_fg_color_8( stream, colors[0] );
				fprintf( stream, "%c", text[ i ] );
				fflush( stream );
			}

			/*
			 * Now we print the successive characters using the fade
			 * colors. This is just like the first for-loop.
			 */
			for( size_t i = j - color_count, k = 0; j < len && i < j; i++, k++ )
			{
				console_fg_color_8(stream, colors[k] );
				fprintf( stream, "%c", text[ i ] );
				fflush( stream );
			}

			time_msleep( millis );
		}

		/*
		 * Finish fading so that the last character ends with the
		 * start color.
		 */
		#ifndef CONSOLE_FADER_BURN_OUT
		console_move_left( stream, color_count - 1 );


		while( color_count > 0 )
		{
			for( size_t i = len - color_count, k = 0; i < len; i++, k++ )
			{
				console_fg_color_8( stream, colors[k] );
				fprintf( stream, "%c", text[ i ] );
				fflush( stream );

				time_msleep( millis * 0.1 ); // 10% of millis since it delays the next line.
			}

			color_count--;
			console_move_left( stream, color_count );
		}
		#endif
	}
	else
	{
		/*
		 * This handles the case when the color_count >= len.
		 */
		for( size_t j = 0; j < len; j++)
		{
			console_move_left( stream, len - j );
#if __apple__
    /* Mac OS X does not support save/restore */
#else
			//console_restore_position(stream);
#endif

			for( size_t i = j, k = 0; i < len && k < color_count; i++, k++ )
			{
				console_fg_color_8(stream, colors[k] );
				fprintf( stream, "%c", text[ i ] );
				fflush( stream );
			}
			time_msleep( millis );
		}

	}

	console_reset( stream );
	console_show_cursor( stream );
	fflush( stream );
}

void console_text_fader( FILE* stream, console_text_fader_style_t style, const char* text )
{
	size_t color_count;
	const int* colors;
	int millis = 0;

	switch( style )
	{
		case TEXT_FADER_BLUE_BEEP:
		{
			colors      = COLORS_BLUE_BEEP;
			color_count = sizeof(COLORS_BLUE_BEEP) / sizeof(COLORS_BLUE_BEEP[0]);
			millis      = 10;
			break;
		}
		case TEXT_FADER_TO_RED:
		{
			colors      = COLORS_FADER_TO_RED;
			color_count = sizeof(COLORS_FADER_TO_RED) / sizeof(COLORS_FADER_TO_RED[0]);
			millis      = 30;
			break;
		}
		case TEXT_FADER_TO_BLUE:
		{
			colors      = COLORS_FADER_TO_BLUE;
			color_count = sizeof(COLORS_FADER_TO_BLUE) / sizeof(COLORS_FADER_TO_BLUE[0]);
			millis      = 15;
			break;
		}
		case TEXT_FADER_TO_GREEN:
		{
			colors      = COLORS_FADER_TO_GREEN;
			color_count = sizeof(COLORS_FADER_TO_GREEN) / sizeof(COLORS_FADER_TO_GREEN[0]);
			millis      = 15;
			break;
		}
		case TEXT_FADER_TO_ORANGE:
		{
			colors      = COLORS_FADER_TO_ORANGE;
			color_count = sizeof(COLORS_FADER_TO_ORANGE) / sizeof(COLORS_FADER_TO_ORANGE[0]);
			millis      = 15;
			break;
		}
		case TEXT_FADER_TO_YELLOW:
		{
			colors      = COLORS_FADER_TO_YELLOW;
			color_count = sizeof(COLORS_FADER_TO_YELLOW) / sizeof(COLORS_FADER_TO_YELLOW[0]);
			millis      = 15;
			break;
		}
		case TEXT_FADER_TO_BLACK:
		{
			colors      = COLORS_FADER_TO_BLACK;
			color_count = sizeof(COLORS_FADER_TO_BLACK) / sizeof(COLORS_FADER_TO_BLACK[0]);
			millis      = 12;
			break;
		}
		case TEXT_FADER_TO_WHITE:
		default: /* fall through */
		{
			colors      = COLORS_FADER_TO_WHITE;
			color_count = sizeof(COLORS_FADER_TO_WHITE) / sizeof(COLORS_FADER_TO_WHITE[0]);
			millis      = 10;
			break;
		}
	}

	console_text_fader_ex( stream, text, colors, color_count, millis );
}

void console_text_faderf( FILE* stream, console_text_fader_style_t style, const char* format, ... )
{
	char fmtbuf[ 256 ];
	va_list args;
	va_start( args, format );
	vsnprintf( fmtbuf, sizeof(fmtbuf), format, args );
	fmtbuf[ sizeof(fmtbuf) - 1 ] = '\0';
	va_end( args );
	console_text_fader( stream, style, fmtbuf );
}

void console_print_divider( FILE* stream, const char* title )
{
	const char* empty = "";

	if( !title )
	{
		title = empty;
	}

	if( title )
	{
		char buffer[ 64 ] = { '\0' };
		size_t len = strlen(title);
		int half_len = len >> 1;
		int half_buffer = sizeof(buffer) >> 1;

		snprintf(buffer, sizeof(buffer), "%*s%*s", half_buffer + half_len, title, half_buffer - half_len, empty);

		for( size_t i = 0; i < sizeof(buffer) - 1; i++ )
		{
			if( isspace( buffer[i] ) )
			{
				buffer[ i ] = '-';
			}
			else
			{
				break;
			}
		}

		for( size_t i = sizeof(buffer) - 1; ; i-- )
		{
			if( isspace( buffer[i] ) || buffer[i] == '\0' )
			{
				buffer[ i ] = '-';
			}
			else
			{
				break;
			}
		}

		buffer[ sizeof(buffer) - 1 ] = '\0';

		fprintf( stream, "--%s--\n", buffer );
	}
}

bool console_command_prompt( char* command_buf, size_t command_buf_size, const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data )
{
	bool not_quiting = true;

	console_fg_color_8( stdout, prompt_color );
	fputs( prompt, stdout );
	console_reset( stdout );

	if( fgets( command_buf, command_buf_size, stdin ) )
	{
		string_trim( command_buf, " \t\r\n" );
		not_quiting = on_cmd( command_buf, data );
	}

	return not_quiting;
}

void console_command_prompt_loop( const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data )
{
	bool quiting = false;
	char command[ 256 ];

	while( !quiting )
	{
		if( !console_command_prompt( command, sizeof(command), prompt, prompt_color, on_cmd, data ) )
		{
			quiting = true;
		}
	}
}


// requires calling setlocale(LC_ALL, "")
void console_curved_box( int x, int y, int w, int h )
{
	if( x <= 0 ) x = 1;
	if( y <= 0 ) y = 1;
	if( w <= 0 ) w = 3;
	if( h <= 0 ) h = 3;

	int inner_width  = w - 2;
	int inner_height = h - 2;

	console_goto(stdout, x, y);
	printf("%lc", CONSOLE_CURVED_BOX_TLCORNER );
	for( int i = 0; i < inner_width; i++ )
	{
		printf("%lc", CONSOLE_CURVED_BOX_HLINE );
	}
	printf("%lc", CONSOLE_CURVED_BOX_TRCORNER );

	for( int i = 0; i < inner_height; i++ ) // vertical lines on left
	{
		console_goto(stdout, x, y + i + 1);
		printf("%lc", CONSOLE_CURVED_BOX_VLINE );
	}

	for( int i = 0; i < inner_height; i++ ) // vertical lines on right
	{
		console_goto(stdout, x + inner_width + 1, y + i + 1);
		printf("%lc", CONSOLE_CURVED_BOX_VLINE );
	}

	console_goto(stdout, x, y + inner_height + 1);
	printf("%lc", CONSOLE_CURVED_BOX_BLCORNER );
	for( int i = 0; i < inner_width; i++ )
	{
		printf("%lc", CONSOLE_CURVED_BOX_HLINE );
	}
	printf("%lc", CONSOLE_CURVED_BOX_BRCORNER );
}

