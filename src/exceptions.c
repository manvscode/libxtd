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
#include <setjmp.h>
#include <string.h>
#include <assert.h>
#include "exceptions.h"

struct exception {
	jmp_buf state;
	unsigned int code;
	unsigned int line;
	char filename[ 256 ];
};

exception_t exception_create( void )
{
	exception_t ex = malloc( sizeof(struct exception) );

	if( ex )
	{
		ex->code          = NO_EXCEPTION;
		ex->line          = 0;
		ex->filename[ 0 ] = '\0';
	}

	return ex;
}

void exception_destroy( exception_t *p_ex )
{
	assert( p_ex && *p_ex );
	free( *p_ex );
	*p_ex = NULL;
}

unsigned int exception_code( const exception_t ex )
{
	assert( ex );
	return ex->code;
}

void exception_set_code( exception_t ex, unsigned int code )
{
	assert( ex );
	ex->code = code;
}

const char* exception_filename( const exception_t ex )
{
	assert( ex );
	return ex->filename;
}

void exception_set_filename( exception_t ex, const char* filename )
{
	assert( ex );
	strncpy( ex->filename, filename, sizeof(ex->filename) );
	ex->filename[ sizeof(ex->filename) - 1 ] = '\0';
}

unsigned int exception_line( const exception_t ex )
{
	assert( ex );
	return ex->line;
}

void exception_set_line( exception_t ex, unsigned int line )
{
	assert( ex );
	ex->line = line;
}

jmp_buf* exception_state( const exception_t ex )
{
	assert( ex );
	return &ex->state;
}

void exception_throw_ex( const exception_t ex, unsigned int error_code, const char* filename, unsigned int line )
{
	exception_set_filename( ex, filename );
	exception_set_line( ex, line );
	longjmp( ex->state, error_code );
}

