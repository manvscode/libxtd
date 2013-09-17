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
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "utility.h"

size_t string_left_trim( char* s, const char* delimeters )
{
	char* start = s;
	assert( s );

	while( *s && strchr(delimeters, *s) )
	{
		++s;
	}

	strcpy( start, s );
	return s - start; /* # of chars removed */
}

size_t string_right_trim( char* s, const char* delimeters )
{
	char *end = s + strlen(s) - 1;
	char *new_end = end;
	assert( s );

	if( s != NULL )
	{
		while( strchr(delimeters, *new_end) && new_end >= s )
		{
			--new_end;
		}
		*(new_end + 1) = '\0';
	}

	return end - new_end;
}

size_t string_trim( char* s, const char* delimeters )
{
	return string_left_trim( s, delimeters ) + string_right_trim( s, delimeters );
}

char* string_to_lower( char* s )
{
	char* p_s = s;
	while( p_s )
	{
		*p_s = tolower( *p_s );
		p_s++;
	}

	return s;
}

char* string_to_upper( char* s )
{
	char* p_s = s;

	while( p_s )
	{
		*p_s = toupper( *p_s );
		p_s++;
	}

	return s;
}
