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
#include <stdlib.h>
#include <wctype.h>
#include <assert.h>
#include <wchar.h>
#include <string.h>
#include "xtd/string.h"

wchar_t* wstring_ndup( const wchar_t* s, size_t len ) /* allocates memory */
{
	wchar_t* result = malloc( sizeof(wchar_t) * (len + 1) );
	if( result )
	{
		wcsncpy( result, s, len + 1 );
	}

	return result;
}

wchar_t* wstring_dup( const wchar_t* s ) /* allocates memory */
{
	size_t len = wcslen( s );
	return wstring_ndup( s, len );
}

size_t wstring_left_trim( wchar_t* s, const wchar_t* delimeters )
{
	wchar_t* start = s;
	assert( s );

	while( *s && wcschr(delimeters, *s) )
	{
		++s;
	}

	memmove( start, s, sizeof(wchar_t) * (wcslen(s) + 1) );
	return (s - start) / sizeof(wchar_t); /* # of chars removed */
}

size_t wstring_right_trim( wchar_t* s, const wchar_t* delimeters )
{
	wchar_t* end = s + wcslen(s) - 1;
	wchar_t* new_end = end;
	assert( s );

	if( s != NULL )
	{
		while( wcschr(delimeters, *new_end) && new_end >= s )
		{
			--new_end;
		}
		*(new_end + 1) = '\0';
	}

	return (end - new_end) / sizeof(wchar_t);
}

size_t wstring_trim( wchar_t* s, const wchar_t* delimeters )
{
	return wstring_left_trim( s, delimeters ) + wstring_right_trim( s, delimeters );
}

wchar_t* wstring_to_lower( wchar_t* s )
{
	wchar_t* p_s = s;

    if( p_s )
    {
        while( *p_s != '\0' )
        {
            *p_s = towlower( *p_s );
            p_s++;
        }
    }

	return s;
}

wchar_t* wstring_to_upper( wchar_t* s )
{
	wchar_t* p_s = s;

    if( p_s )
    {
        while( *p_s != '\0' )
        {
            *p_s = towupper( *p_s );
            p_s++;
        }
    }

	return s;
}

wchar_t* wstring_replace( const wchar_t* orig, const wchar_t* rep, const wchar_t* with )
{
    wchar_t* result; // the return string
    const wchar_t* ins;    // the next insert point
    wchar_t* tmp;    // varies
    size_t len_rep;  // length of rep
    size_t len_with; // length of with
    size_t len_front; // distance between rep and end of last rep
    size_t count;    // number of replacements

    if(!orig)
    {
        return NULL;
    }
    if(!rep)
    {
        rep = L"";
    }
    len_rep = wcslen(rep);
    if(!with)
    {
        with = L"";
    }

    len_with = wcslen(with);

    ins = orig;
    for (count = 0; (tmp = wcsstr(ins, rep)) != NULL; ++count)
    {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    tmp = result = malloc(sizeof(wchar_t) * (wcslen(orig) + (len_with - len_rep) * count + 1));

    if(!result)
    {
        return NULL;
    }

    while(count--)
    {
        ins = wcsstr(orig, rep);
        len_front = (ins - orig) / sizeof(wchar_t);
        tmp = wcsncpy(tmp, orig, len_front) + len_front;
        tmp = wcscpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }

    wcscpy(tmp, orig);
    return result;
}

wchar_t* wstring_substring( const wchar_t* str, size_t start, size_t end )
{
    size_t len = (end - start) / sizeof(wchar_t);
    wchar_t* result = malloc( sizeof(wchar_t) * (len + 1) );

    if( result )
    {
        wcsncpy( result, str + start, len );
        result[ len ] = '\0';
    }

    return result;
}
