#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "utility.h"

void progress_task( int* percent, void* data )
{
	*percent += rand() % 20;
	usleep( 50000 );
}

int main()
{
#if 1
	for( int i = 0; i < 256; i++ )
	{
		printf( "%s%s", console_fg_color_256(15), console_bg_color_256( i ) );
		printf( " %02x ", i );

		if( (i+1) % 16 == 0 )
		{
			printf( console_reset() );
			printf( "\n" );
		}
	}
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
#endif
	const int progress_bar_width = 40;

	const int colors1[] = { 0xdf, 0xde, 0xdd, 0xdc };
	console_progress_indicator_ex( "Loading support bundle...", progress_bar_width, colors1, 4, progress_task, NULL );
	console_progress_indicator("Loading tests...", progress_task, NULL );
	//console_progress_indicator_ex( "Generating world peace...", progress_bar_width, 0x14, 0, 0, progress_task, NULL );
	//console_progress_indicator_ex( "Generating world peace...", progress_bar_width, 0x1c, 0, 0 );

	return 0;
}
