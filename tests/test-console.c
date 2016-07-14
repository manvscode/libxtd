#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "utility.h"


static void progress_task( int* percent, void* data );
static bool process_cmd( const char* command, void* data );

static void console_fader( const char* text, const int* colors, size_t color_count, int millis )
{
    size_t len = strlen(text);

    for( size_t j = 0; j < len; j++ )
    {
	    console_move_left(1000);
        for( size_t i = 0, k = 0; i < color_count && j < color_count; i++, k++ )
        {
            console_fg_color_256(colors[k]);
            printf( "%c", text[ i ] );
            fflush( stdout );
        }
        for( size_t i = 0; j > color_count && i < j - color_count; i++ )
        {
            console_fg_color_256(colors[0]);
            printf( "%c", text[ i ] );
            fflush( stdout );
        }
        for( size_t i = j - color_count, k = 0; j < (len - color_count) && i < j; i++, k++ )
        {
            console_fg_color_256(colors[k]);
            printf( "%c", text[ i ] );
            fflush( stdout );
        }
        usleep( millis * 1000 );
    }

	console_reset();
	fflush( stdout );
}


int main()
{
    console_fg_color_8( CONSOLE_COLOR8_YELLOW );
    printf( "Type 'help' to see commands.\n" );
    console_command_prompt( ">> ", 0x21, process_cmd, NULL );
	return 0;
}

bool process_cmd( const char* command, void* data )
{
    //printf( "Command: %s (len = %d)\n", command, strlen(command) );

    if( strcmp(command, "quit") == 0 )
    {
        return false;
    }
    else if( strcmp(command, "help") == 0 )
    {
        printf( "Possible Commands\n" );
        printf( "--------------------\n" );
        printf( "  %6s   %-50s\n", "colors1", "Show all 256 colors." );
        printf( "  %6s   %-50s\n", "colors2", "Show all 256 colors." );
        printf( "  %6s   %-50s\n", "lwp", "Demo progress bar." );
        printf( "  %6s   %-50s\n", "mu", "Demo memory utilization." );
        printf( "  %6s   %-50s\n", "fader", "Demo fader wolf." );
        printf( "  %6s   %-50s\n", "clear", "Clear the screen." );
        printf( "  %6s   %-50s\n", "quit", "Quit the app." );
    }
    else if( strcmp(command, "colors1") == 0 )
    {
        for( int i = 0; i < 256; i++ )
        {
            console_fg_color_256(15);
            console_bg_color_256( i );
            printf( " %02x ", i );

            if( (i+1) % 16 == 0 )
            {
                console_reset();
                printf( "\n" );
            }
        }
    }
    else if( strcmp(command, "colors2") == 0 )
    {
        for( int i = 0; i < 256; i++ )
        {
            console_fg_color_256( i );
            printf( " %02x ", i );

            if( (i+1) % 16 == 0 )
            {
                console_reset();
                printf( "\n" );
            }
        }
    }
    else if( strcmp(command, "lwp") == 0 )
    {
	    console_progress_indicator("Loading world peace...", PROGRESS_INDICATOR_STYLE_BLUE, progress_task, NULL );
    }
    else if( strcmp(command, "mu") == 0 )
    {
        const int INTENSITY_COLORS[] = {
            0x02, 0x22, 0x28,
            0x9a, 0xe2, 0xdc,
            0xd6, 0xd0, 0xc4
        };
        int percent = rand() % 101;
        printf( "%3d%% ", percent );
        console_bar_graph( 16, ' ', INTENSITY_COLORS, sizeof(INTENSITY_COLORS) / sizeof(INTENSITY_COLORS[0]), 0xea, percent );
        printf( "\n" );
    }
    else if( strcmp(command, "fader") == 0 )
    {
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
        const char* text1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor";
        const char* text2 = "incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis";
        const char* text3 = "nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.";
        const char* text4 = "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu";
        const char* text5 = "fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in";
        const char* text6 = "culpa qui officia deserunt mollit anim id est laborum.";

        console_fader( text1, colors2, 15, 50 );
        printf( "\n" );
#if 0
        console_fader( text2, colors2, 15, 50 );
        printf( "\n" );
        console_fader( text3, colors2, 15, 50 );
        printf( "\n" );
        console_fader( text4, colors2, 15, 50 );
        printf( "\n" );
        console_fader( text5, colors2, 15, 50 );
        printf( "\n" );
        console_fader( text6, colors2, 15, 50 );
        printf( "\n" );
#endif
    }
    else if( *command == '\0' )
    {
        // do nothing
	    console_move_left(1000);
    }
    else if( strcmp(command, "clear") == 0 )
    {
        console_clear_screen_all();
    }
    else
    {
        console_fg_color_8( CONSOLE_COLOR8_RED );
        printf( "ERROR:" );
        console_reset();
        printf( " Unrecognized command '%s'\n", command );
    }

    return true;
}

void progress_task( int* percent, void* data )
{
	*percent += rand() % 20;
	usleep( 50000 );
}




