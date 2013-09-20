/*
 * Copyright (C) 2010 by Joseph A. Marrero. http://www.manvscode.com/
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


int main( int argc, char *argv[] )
{
	if( argc < 1 )
	{
		return -1;
	}

	char* file = argv[ 1 ];
	size_t size = 12425672300;
	printf( "size = %s\n", size_in_units( size, unit_bytes, 0 ) );
	printf( "size = %s\n", size_in_units( size, unit_megabytes, 2 ) );
	printf( "size = %s\n", size_in_units( size, unit_mebibytes, 2 ) );
	printf( "app size = %s\n", appropriate_size( size, false, 1 ) );

	size_t text_size = 0;
	char* text = file_load_contents( file, &text_size );
	if( text )
	{
		print_divider( stdout, file );
		printf( "%s", text );
		print_divider( stdout, NULL );
		free( text );
	}

	return 0;
}
