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
#include <ctype.h>
#include <assert.h>
#include "xtd/string.h"

char* string_ndup( const char* s, size_t len ) /* allocates memory */
{
	char* result = malloc( len + 1 );
	if( result )
	{
		strncpy( result, s, len + 1 );
	}

	return result;
}

char* string_dup( const char* s ) /* allocates memory */
{
	size_t len = strlen( s );
	return string_ndup( s, len );
}

size_t string_left_trim( char* s, const char* delimeters )
{
	char* start = s;
	assert( s );

	while( *s && strchr(delimeters, *s) )
	{
		++s;
	}

	memmove( start, s, strlen(s) + 1 );
	return s - start; /* # of chars removed */
}

size_t string_right_trim( char* s, const char* delimeters )
{
	char* end = s + strlen(s) - 1;
	char* new_end = end;
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

    if( p_s )
    {
        while( *p_s != '\0' )
        {
            *p_s = tolower( *p_s );
            p_s++;
        }
    }

	return s;
}

char* string_to_upper( char* s )
{
	char* p_s = s;

    if( p_s )
    {
        while( *p_s != '\0' )
        {
            *p_s = toupper( *p_s );
            p_s++;
        }
    }

	return s;
}

void string_random( string_random_type_t type, char* string, size_t length )
{
	const char* pool = NULL;
	size_t max = 0L;
	size_t i;

	switch( type )
	{
		case RAND_STRING_ALPHA:
			pool = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			break;
		case RAND_STRING_HEX:
			pool = "0123456789abcdef";
			break;
		case RAND_STRING_NUMERIC:
			pool = "0123456789";
			break;
		case RAND_STRING_NO_ZERO:
			pool = "123456789";
			break;
		case RAND_STRING_DISTINCT:
			pool = "2345679ACDEFHJKLMNPRSTUVWXYZ";
			break;
		case RAND_STRING_ALPHA_NUMERIC:
		default:
			pool = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			break;
	}

	// Largest pool key
	max = strlen( pool );


	int contains_alpha = 0;
	int contains_num   = 0;

	for( i = 0; i < length; i++ )
	{
		// Select a random character from the pool and add it to the string
		string[ i ] = pool[ rand() % max ];

		if( isalpha( string[ i ] ) )
		{
			contains_alpha = 1;
		}
		else if( isdigit( string[ i ] ) )
		{
			contains_num = 1;
		}
	}

	// Make sure alnum strings contain at least one letter and one digit
	if( (type == 0 || type == 2 || type == 5) && length > 1 )
	{
		if( !contains_alpha )
		{
			// Add a random letter
			string[ rand() % (length + 1) ] = 65 + (rand() % 26);
		}

		if( !contains_num )
		{
			// Add a random digit
			string[ rand() % (length + 1) ] = 48 + (rand() % 10);
		}
	}
	string[ length ] = '\0';
}

const char* string_ordinal( long number )
{
	if( number % 100 > 10 && number % 100 < 14 )
	{
		return "th";
	}

	switch( number % 10 )
	{
		case 1:
			return "st";
		case 2:
			return "nd";
		case 3:
			return "rd";
		default:
			return "th";
	}
}

bool string_starts_with( const char* str, const char* prefix )
{
	bool result = true;
	char* s = (char*) str;
	char* p = (char*) prefix;

	assert( s && "String is null" );
	assert( p && "Prefix is null" );

	while( *p && result )
	{
		if( *s++ != *p++ )
		{
			result = false;
		}
	}

	return result;
}

char* string_replace( const char* orig, const char* rep, const char* with )
{
    char* result; // the return string
    const char* ins;    // the next insert point
    char* tmp;    // varies
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
        rep = "";
    }
    len_rep = strlen(rep);
    if(!with)
    {
        with = "";
    }

    len_with = strlen(with);

    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)) != NULL; ++count)
    {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if(!result)
    {
        return NULL;
    }

    while(count--)
    {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }

    strcpy(tmp, orig);
    return result;
}

char* string_substring( const char* str, size_t start, size_t end )
{
    size_t len = end - start;
    char* result = malloc( len + 1 );

    if( result )
    {
        strncpy( result, str + start, len );
        result[ len ] = '\0';
    }

    return result;
}


// like strtok() but can handle repeated delimeters (i.e. "one,,three").
char* string_tokenize_r( char* str, const char* delims, char** saveptr )
{
	char* p = NULL;
	char* ret = NULL;

	if( str != NULL )
	{
		*saveptr = str;
	}

	if( *saveptr == NULL )
	{
		return NULL;
	}

	if( (p = strpbrk(*saveptr, delims)) != NULL )
	{
		*p  = '\0';
		ret = *saveptr;
		*saveptr = ++p;

	}
	else if( **saveptr )
	{
		ret = *saveptr;
		*saveptr = NULL;
	}

	return ret;
}


char* string_tokenize( char* str, const char* delims )
{
	static char* saveptr = NULL;

	if(str)
	{
		saveptr = str;
	}

	return string_tokenize_r( str, delims, &saveptr );
}

size_t string_hash( const char* s )
{
	size_t hash = 0;
	const unsigned char* us = (const unsigned char*) s;

	while( *us != '\0')
	{
		hash = 31 * hash + *us;
		us++;
	}

	return hash;
}

size_t string_nhash( const char* s, size_t len )
{
	size_t hash = 0;
	const unsigned char* us = (const unsigned char*) s;

	for( size_t i = 0; i < len; i++ )
	{
		hash = 31 * hash + us[ i ];
	}

	return hash;
}

size_t mb_strlen( const char* utf8 )
{
	size_t len = 0;

	while( *utf8 )
	{
		int i = mblen( utf8, 2 );
		if( i > 0 )
		{
			len += 1;
			utf8 += i;
		}
		else
		{
			break;
		}
	}

	return len;
}

size_t mb_size_at_char( const char* utf8, int character )
{
	size_t size = 0;
	int i = 0;

	while( *utf8 && i < character )
	{
		int cnt = mblen( utf8, 2 );

		if( cnt > 0 )
		{
			size += cnt;
			utf8 += cnt;
			i += 1;
		}
		else
		{
			break;
		}
	}

	return size;
}

