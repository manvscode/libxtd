#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utility.h"
#include "console.h"


static bool progress_task( int* percent, void* data );
static bool process_cmd( const char* command, void* data );
static const char* text[] = {
    "Happy ye leaves. whenas those lily hands,",
    "Which hold my life in their dead doing might,",
    "Shall handle you, and hold in love's soft bands,",
    "Like captives trembling at the victor's sight.",
    "And happy lines on which, with starry light,",
    "Those lamping eyes will deign sometimes to look,",
    "And read the sorrows of my dying sprite,",
    "Written with tears in heart's close bleeding book.",
    "And happy rhymes! bathed in the sacred brook",
    "Of Helicon, whence she derived is,",
    "When ye behold that angel's blessed look,",
    "My soul's long lacked food, my heaven's bliss.",
    "Leaves, lines, and rhymes seek her to please alone,",
    "Whom if ye please, I care for other none.",
};

int main()
{
#if 0
    console_fg_color_8( stdout, CONSOLE_COLOR8_YELLOW );
    printf( "Type 'help' to see commands.\n" );
#else
    console_text_faderf( stdout, TEXT_FADER_TO_YELLOW, "Type '%s' to see commands.", "help" );
    fputs( "\n", stdout );
#endif
    console_command_prompt( ">> ", 0x3d, process_cmd, NULL );
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
        printf( "  %6s   %-50s\n", "fader1", "Demo text fader." );
        printf( "  %6s   %-50s\n", "fader2", "Demo text fader." );
        printf( "  %6s   %-50s\n", "clear", "Clear the screen." );
        printf( "  %6s   %-50s\n", "quit", "Quit the app." );
    }
    else if( strcmp(command, "colors1") == 0 )
    {
        for( int i = 0; i < 256; i++ )
        {
            console_fg_color_256( stdout, 15 );
            console_bg_color_256( stdout, i );
            printf( " %02x ", i );

            if( (i+1) % 16 == 0 )
            {
                console_reset( stdout );
                printf( "\n" );
            }
        }
    }
    else if( strcmp(command, "colors2") == 0 )
    {
        for( int i = 0; i < 256; i++ )
        {
            console_fg_color_256( stdout, i );
            printf( " %02x ", i );

            if( (i+1) % 16 == 0 )
            {
                console_reset( stdout );
                printf( "\n" );
            }
        }
    }
    else if( strcmp(command, "lwp") == 0 )
    {
	    console_progress_indicator( stdout, "Loading world peace...", PROGRESS_INDICATOR_STYLE_BLUE, progress_task, NULL );
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
        console_bar_graph( stdout, 16, ' ', INTENSITY_COLORS, sizeof(INTENSITY_COLORS) / sizeof(INTENSITY_COLORS[0]), 0xea, percent );
        printf( "\n" );
    }
    else if( strcmp(command, "fader1") == 0 )
    {
        size_t len = sizeof(text) / sizeof(text[0]);
        console_text_fader_style_t style = TEXT_FADER_TO_WHITE;

        for( int i = 0; i < len; i++ )
        {
            console_text_fader( stdout, style, text[i] );
            printf( "\n" );
        }
    }
    else if( strcmp(command, "fader2") == 0 )
    {
        size_t len = sizeof(text) / sizeof(text[0]);
        console_text_fader_style_t style = TEXT_FADER_BLUE_BEEP;

        for( int i = 0; i < len; i++ )
        {
            console_text_fader( stdout, style, text[i] );
            printf( "\n" );
        }
    }
    else if( *command == '\0' )
    {
        // do nothing
	    console_move_left( stdout, 1000);
    }
    else if( strcmp(command, "clear") == 0 )
    {
        console_clear_screen_all( stdout );
    }
    else
    {
        console_fg_color_8( stdout, CONSOLE_COLOR8_RED );
        printf( "ERROR:" );
        console_reset( stdout );
        printf( " Unrecognized command '%s'\n", command );
    }

    return true;
}

bool progress_task( int* percent, void* data )
{
	*percent += rand() % 10;

    int delays[] = {
        250, 50, 10, 25, 100
    };

    time_msleep( delays[ rand() % 5 ] );
    return true;
}
