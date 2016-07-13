#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "utility.h"

static void progress_task( int* percent, void* data )
{
	*percent += rand() % 20;
	usleep( 500000 );
}


static void console_fader( const char* text, const int* colors, size_t color_count, int millis )
{
    size_t len = strlen(text);

    for( size_t j = 0; j < len; j++ )
    {
	    console_move_left(1000);
        for( size_t i = 0; i < j; i++ )
        {
            if( i < j - color_count)
            {
                console_fg_color_256( colors[ 0 ] );
            }
            else
            {
                console_fg_color_256( colors[ 14 ] );
            }
            printf( "%c", text[ i ] );
            fflush( stdout );
            usleep( millis * 1000 );
        }
    }

	printf( "%s", console_reset() );
	fflush( stdout );
}


int main()
{
#if 1
	for( int i = 0; i < 256; i++ )
	{
		console_fg_color_256(15);
        console_bg_color_256( i );
		printf( " %02x ", i );

		if( (i+1) % 16 == 0 )
		{
			printf( console_reset() );
			printf( "\n" );
		}
	}
    printf( "\n" );
#endif

#if 0
	printf( "\n" );
	for( int i = 0; i < 256; i++ )
	{
		printf( "%s", console_fg_color_256(i) );
		printf( " %02x ", i );

		if( (i+1) % 16 == 0 )
		{
			printf( console_reset() );
			printf( "\n" );
		}
	}

	printf( "\n" );
	for( int i = 0; i < 256; i++ )
	{
		printf( "%s%s%s", console_bold(), console_bold(), console_fg_color_256(i) );
		printf( " %02x ", i );

		if( (i+1) % 16 == 0 )
		{
			printf( console_reset() );
			printf( "\n" );
		}
	}
	const int progress_bar_width = 40;

#endif
    //printf( "%s", console_clear_screen_all() );
	console_progress_indicator("Loading tests...", PROGRESS_INDICATOR_STYLE_BLUE, progress_task, NULL );
	console_progress_indicator("Installing World Peace...", PROGRESS_INDICATOR_STYLE_FADE, progress_task, NULL );
	console_progress_indicator("Memory Utilization", PROGRESS_INDICATOR_STYLE_INTENSITY, progress_task, NULL );
	const int colors2[] = {
        0xff, 0xfe, 0xfd, 0xfc, 0xfb,
        0xfa, 0xf9, 0xf8, 0xf7, 0xf6,
        0xf5, 0xf4, 0xf3, 0xf2, 0xf1
	};
    /*
	const int colors2[] = {
		0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1,
		0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
		0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
	};
    */

    //console_fader( "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ\n", colors2, 15, 10 );

	return 0;
}
