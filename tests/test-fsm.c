/*
 * Copyright (C) 2010 by Joseph A. Marrero and Shrewd LLC. http://www.manvscode.com/
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utility.h"

typedef enum app_events {
	EVT_INPUT_MESSAGE,
	EVT_ENCRYPT_MESSAGE,
	EVT_DECRYPT_MESSAGE,
	EVT_PRINT_MESSAGE,
	EVT_DISPLAY_MENU,
	EVT_EXIT
} app_events_t;

fsm_event_t app_on_menu( void* data );
fsm_event_t app_on_exit( void* data );
fsm_event_t app_on_input_message( void* data );
fsm_event_t app_on_encrypt_message( void* data );
fsm_event_t app_on_decrypt_message( void* data );
fsm_event_t app_on_print_message( void* data );

fsm_transition_t app_transitions[] = {
	{ app_on_menu, EVT_INPUT_MESSAGE, app_on_input_message },
	{ app_on_menu, EVT_ENCRYPT_MESSAGE, app_on_encrypt_message },
	{ app_on_menu, EVT_DECRYPT_MESSAGE, app_on_decrypt_message },
	{ app_on_menu, EVT_PRINT_MESSAGE, app_on_print_message },
	{ app_on_menu, EVT_DISPLAY_MENU, app_on_menu },
	{ app_on_input_message, EVT_DISPLAY_MENU, app_on_menu },
	{ app_on_encrypt_message, EVT_DISPLAY_MENU, app_on_menu },
	{ app_on_decrypt_message, EVT_DISPLAY_MENU, app_on_menu },
	{ app_on_print_message, EVT_DISPLAY_MENU, app_on_menu },
	{ app_on_menu, EVT_EXIT, app_on_exit },
};

struct {
	char buffer[ 1024 ];
	bool encrypted;
} app_data = { "\0", false };

int main( int argc, char *argv[] )
{
	fsm_t* fsm = fsm_create( sizeof(app_transitions) / sizeof(app_transitions[0]), app_transitions, app_on_menu, app_on_exit );
	fsm_run( fsm, NULL );
	fsm_destroy( &fsm );
	return 0;
}


fsm_event_t app_on_menu( void* data )
{
	char input;
	printf( "--------------[ MENU ]-------------\n" );
	printf( "    a.) Input Message\n" );
	printf( "    b.) Encrypt Message\n" );
	printf( "    c.) Decrypt Message\n" );
	printf( "    d.) Print Message\n" );
	printf( "    e.) Exit\n" );
	printf( "-----------------------------------\n" );
	printf( "Selection: " );

	char input_buffer[6];
	fgets( input_buffer, sizeof(input_buffer), stdin );
	input_buffer[ sizeof(input_buffer) - 1 ] = '\0';
	sscanf( input_buffer, "%c", &input );
	printf( "\n" );
	fsm_event_t e;

	switch( input )
	{
		case 'A':
		case 'a':
			e = EVT_INPUT_MESSAGE;
			break;
		case 'B':
		case 'b':
			e = EVT_ENCRYPT_MESSAGE;
			break;
		case 'C':
		case 'c':
			e = EVT_DECRYPT_MESSAGE;
			break;
		case 'D':
		case 'd':
			e = EVT_PRINT_MESSAGE;
			break;
		case 'E':
		case 'e':
			e = EVT_EXIT;
			break;
		default:
			e = EVT_DISPLAY_MENU;
			break;
	}

	return e;
}

fsm_event_t app_on_input_message( void* data )
{
	printf( "\n" );
	printf( "Type your message: " );
	fgets( app_data.buffer, sizeof(app_data.buffer), stdin );
	app_data.buffer[ sizeof(app_data.buffer) - 1 ] = '\0';
	printf( "\n" );
	return EVT_DISPLAY_MENU;
}

fsm_event_t app_on_encrypt_message( void* data )
{
	printf( "\n" );
	app_data.encrypted = true;
	printf( "Encrypting...\n" );
	caesar_cypher_encryption( app_data.buffer, sizeof(app_data.buffer), 23 );
	return EVT_DISPLAY_MENU;
}

fsm_event_t app_on_decrypt_message( void* data )
{
	printf( "\n" );
	app_data.encrypted = false;
	printf( "Decrypting...\n" );
	caesar_cypher_decryption( app_data.buffer, sizeof(app_data.buffer), 23 );
	return EVT_DISPLAY_MENU;
}

fsm_event_t app_on_print_message( void* data )
{
	printf( "\n" );
	if( app_data.encrypted )
	{
		printf( "Encrypted Message: " );
	}
	else
	{
		printf( "Message: " );
	}

	for( size_t i = 0; i < sizeof(app_data.buffer); i++ )
	{
		if( app_data.encrypted )
		{
			if( isprint(app_data.buffer[i]) )
			{
				printf( "%c", app_data.buffer[i] );
			}
			else
			{
				printf( "?" );
			}
		}
		else
		{
			printf( "%c", app_data.buffer[i] );
		}
	}

	printf( "\n" );

	return EVT_DISPLAY_MENU;
}

fsm_event_t app_on_exit( void* data )
{
	printf( "Exiting...\n" );
	return EVT_DISPLAY_MENU;
}
