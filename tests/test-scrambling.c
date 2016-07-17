/*
 * Copyright (C) 2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#include <string.h>
#include <time.h>
#include "utility.h"
#include "console.h"


int main( int argc, char *argv[] )
{
	char SEED[ 32 ];
	char text[ 512 ];
	size_t len;
	size_t i;
	srand( time(NULL) );


	string_random( 0, SEED, sizeof(SEED) - 1 );
	SEED[ sizeof(SEED) - 1 ] = '\0';

	strcpy( text, "Joseph Marrero is an awesome computer programmer." );
	len = strlen(text);

	text[ sizeof(text) - 1 ] = '\0';

	unsigned short pivot = rand();


	buffer_scramble( SEED, text, len, pivot );
	text[ sizeof(text) - 1 ] = '\0';

	console_print_divider( stdout, "[ Scrambling Text Test ]" );
	printf( "      Pivot = [%d]\n", pivot );
	printf( "       SEED = [%s]\n", SEED );
	printf( "  Scrambled = [%s]\n", text );
	printf( "  Scrambled = [" );

	for( i = 0; i < len; i++ )
	{
		printf( "%02x", text[i] );
	}
	printf( "]\n" );

	buffer_unscramble( SEED, text, len, pivot );
	text[ sizeof(text) - 1 ] = '\0';
	printf( "Unscrambled = [%s]\n", text );
	printf( "Unscrambled = [" );
	for( i = 0; i < len; i++ )
	{
		printf( "%02x", text[i] );
	}
	printf( "]\n" );

	return 0;
}
