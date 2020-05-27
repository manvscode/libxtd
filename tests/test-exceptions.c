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
#include "xtd/exceptions.h"

typedef enum errors {
	ERR_NONE = 0,
	ERR_BAD_FILE
} errors_t;


int main( int argc, char *argv[] )
{
	exception_t ex = exception_create( );

	printf( "Attempting to open a file.\n" );

	exception_try( ex )
	{
		FILE *file = fopen( "this-file-does-not-exist.txt", "r" );

		if( !file )
		{
			exception_throw( ex, ERR_BAD_FILE );
		}

		printf( "This code is not reachable." );
		fclose( file );
	}
	exception_catch( ex, ERR_BAD_FILE )
	{
		printf( "ERR_BAD_FILE exception was caught.\n" );
	}

	exception_destroy( &ex );

	return 0;
}
