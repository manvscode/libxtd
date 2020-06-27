#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "xtd/time.h"
#include "xtd/string.h"
#include "xtd/console.h"


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
	signal( SIGWINCH, on_window_changed );
#if 0
	console_fg_color_8( stdout, CONSOLE_COLOR8_YELLOW );
	printf( "Type 'help' to see commands.\n" );
#else
	console_text_faderf( stdout, TEXT_FADER_TO_YELLOW, "Type '%s' to see commands.", "help" );
	fputs( "\n", stdout );
#endif
	console_command_prompt_loop( ">> ", 0x3d, process_cmd, NULL );
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
		printf( "  %10s   %-50s\n", "reset", "Reset the console." );
		printf( "  %10s   %-50s\n", "document", "Set the document." );
		printf( "  %10s   %-50s\n", "cwd", "Set the current working directory." );
		printf( "  %10s   %-50s\n", "colors2", "Show all 256 colors." );
		printf( "  %10s   %-50s\n", "lwp", "Demo progress bar." );
		printf( "  %10s   %-50s\n", "lm", "Demo progress bar fade." );
		printf( "  %10s   %-50s\n", "mu", "Demo memory utilization." );
		printf( "  %10s   %-50s\n", "fader1", "Demo text fader." );
		printf( "  %10s   %-50s\n", "fader2", "Demo text fader." );
		printf( "  %10s   %-50s\n", "fader3", "Demo text fader." );
		printf( "  %10s   %-50s\n", "clear", "Clear the screen." );
		printf( "  %10s   %-50s\n", "size", "Get the window size." );
		printf( "  %10s   %-50s\n", "set-size", "Set the window size." );
		printf( "  %10s   %-50s\n", "quit", "Quit the app." );
	}
	else if( strcmp(command, "reset") == 0 )
    {
        console_reset( stdout );

    }
	else if( strcmp(command, "document") == 0 )
    {
        console_set_document( stdout, "file:some_file_here");
    }
	else if( strcmp(command, "cwd") == 0 )
    {
        char path[ 512 ];
        if( !getcwd(path, sizeof(path)) )
		{
			char cwd[512];
			snprintf(cwd, sizeof(cwd), "file:%s", cwd);
			console_set_working_directory( stdout, path );
		}
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
	else if( strcmp(command, "lm") == 0 )
	{
		console_fg_color_256( stdout, CONSOLE_COLOR8_YELLOW );
		printf(" TEST -|>  ");
		console_reset(stdout);
		console_progress_indicator( stdout, "Loading magic...", PROGRESS_INDICATOR_STYLE_FADE, progress_task, NULL );
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
	else if( strcmp(command, "fader3") == 0 )
	{
		size_t len = sizeof(text) / sizeof(text[0]);
		console_text_fader_style_t style = TEXT_FADER_TO_WHITE;

		printf( "    " );
		console_text_fader( stdout, style, "One big Test" );
		printf( "\n" );
		for( int i = 0; i < len; i++ )
		{
			printf( "    " );
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
	else if( strcmp(command, "diagonal") == 0 )
	{
		console_clear_screen_all( stdout );

		int rows = 0;
		int cols = 0;
		console_size(stdout, &rows, &cols);

		for( int x = 0; x < cols; x += 1)
		{
			for( int y = 0; y < rows; y += 1)
			{
				console_goto( stdout, x, y );
				if( x == y )
				{
					console_bg_color_256( stdout, CONSOLE_COLOR256_BLUE );
					fprintf( stdout, " " );
				}
				else
				{
					console_bg_color_256( stdout, CONSOLE_COLOR256_GREY_23 );
					fprintf( stdout, " " );
				}
				console_reset( stdout );
			}
		}
	}
	else if( strcmp(command, "size") == 0 )
	{
		int rows = 0;
		int cols = 0;
		console_size( stdout, &rows, &cols );
		printf("%dx%d\n", cols, rows );
	}
	else if( string_starts_with(command, "set-size") )
	{
		int rows = 0;
		int cols = 0;
		if( sscanf( command, "set-size %d %d", &rows, &cols ) == 2 )
		{
			console_set_size( stdout, rows, cols );
			printf("Set size to %dx%d\n", cols, rows );
		}
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
