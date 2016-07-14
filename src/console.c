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
#include <string.h>
#include <ctype.h>
#include "utility.h"

#ifdef _WIN32
#define snprintf _snprintf
#endif

void print_divider( FILE* fd, const char* title )
{
	const char* empty = "";

	if( !title )
	{
		title = empty;
	}

	if( title )
	{
		char buffer[ 64 ] = { '\0' };
		size_t len      = strlen(title);
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

		fprintf( fd, "--%s--\n", buffer );
	}
}

void console_fg_color_8( int color )
{
    printf( "\033[%dm", color );
}

void console_fg_bright_color_8( int color )
{
    printf( "\033[%d;1m", color );
}

void console_fg_color_256( int color )
{
	printf( "\033[38;5;%dm", color );
}

void console_bg_color_256( int color )
{
	printf( "\033[48;5;%dm", color );
}

void console_bold( void )
{
    printf( "\033[1m" );
}

void console_underline( void )
{
    printf( "\033[4m" );
}

void console_reversed( void )
{
    printf( "\033[7m" );
}

void console_reset( void )
{
    printf( "\033[0m" );
}

void console_save_position( void )
{
    printf( "\033[s" );
}

void console_restore_position( void )
{
    printf( "\033[u" );
}

void console_move_up( int n )
{
	printf( "\033[%dA", n );
}

void console_move_down( int n )
{
	printf( "\033[%dB", n );
}

void console_move_left( int n )
{
	printf( "\033[%dD", n );
}

void console_move_right( int n )
{
	printf( "\033[%dC", n );
}

void console_next_line( int n )
{
	printf( "\033[%dE", n );
}

void console_prev_line( int n )
{
	printf( "\033[%dF", n );
}

void console_set_column( int x )
{
	printf( "\033[%dG", x );
}

void console_goto( int x, int y )
{
	printf( "\033[%d;%dH", y, x );
}

void console_clear_screen( int type )
{
	printf( "\033[%dJ", type );
}

void console_clear_line( int type )
{
	printf( "\033[%dK", type );
}

void console_bar_graph( int bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent )
{
	const int blocks = (bar_width * percent) / 100;

	for( int j = 0; j < bar_width; j++ )
	{
		int color_idx = (color_count * j) / bar_width;
		if( j <= blocks )
		{
			if( bar_symbol == ' ' )
            {
                console_bg_color_256( colors[color_idx] );
            }
            else
            {
                console_fg_color_256( colors[color_idx] );
            }
		}
		else
		{
			if( bar_symbol == ' ' )
            {
                console_bg_color_256( bkg_color );
            }
            else
            {
                console_fg_color_256( bkg_color );
            }
		}
		printf( "%c", bar_symbol );
	}
	console_reset();
	fflush( stdout );
}

static inline void __console_progress_indicator_ex( const char* task, int progress_bar_width, char progress_bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent )
{

#if 0
	printf( "%s[", console_move_left(1000) );
#else
    console_clear_line_all();
    console_set_column( 0 );
	//printf( "[" );
#endif

    console_bar_graph( progress_bar_width, progress_bar_symbol, colors, color_count, bkg_color, percent );
    //printf( "]" );
	printf( " [%3d%%] %s", percent, task );
	fflush( stdout );
}

void console_progress_indicator_ex( const char* task, int progress_bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, console_progress_fxn_t fxn, void* data )
{

	for( int percent = 0; percent < 100; fxn( &percent, data ) )
	{
		__console_progress_indicator_ex( task, progress_bar_width, bar_symbol, colors, color_count, bkg_color, percent );
	}
	__console_progress_indicator_ex( task, progress_bar_width, bar_symbol, colors, color_count, bkg_color, 100 );
	printf( "\n" );
}

void console_progress_indicator( const char* task, progress_indictor_style_t style, console_progress_fxn_t fxn, void* data )
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
            const int FADE_COLORS[] = {
                0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1,
                0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
                0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
            };
            colors      = FADE_COLORS;
            color_count = sizeof(FADE_COLORS) / sizeof(FADE_COLORS[0]);
            bkg_color   = 0xe9;
            break;
        }
        case PROGRESS_INDICATOR_STYLE_INTENSITY:
        {
            const int INTENSITY_COLORS[] = {
                0x02, 0x22, 0x28,
                0x9a, 0xe2, 0xdc,
                0xd6, 0xd0, 0xc4
            };
            colors      = INTENSITY_COLORS;
            color_count = sizeof(INTENSITY_COLORS) / sizeof(INTENSITY_COLORS[0]);
            bkg_color   = 0xeb;
            break;
        }
        case PROGRESS_INDICATOR_STYLE_BLUE:
        default: /* fall through */
        {
	        const int BLUE = 0x15;
            colors         = &BLUE;
            color_count    = 1;
            bkg_color      = 0x11;
            break;
        }
    }

	console_progress_indicator_ex( task, progress_bar_width, progress_bar_symbol, colors, color_count, bkg_color, fxn, data );
}

void console_command_prompt( const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data )
{
    bool quiting = false;
    char command[ 256 ];

    while( !quiting )
    {
        console_fg_color_256( prompt_color );
        printf( prompt );
        console_reset();

        fgets( command, sizeof(command), stdin );
        string_trim( command, " \t\r\n" );

        if( !on_cmd( command, data ) )
        {
            quiting = true;
        }
    }
}
