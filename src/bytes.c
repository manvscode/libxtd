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
#include <limits.h>
#include <string.h>
#include "utility.h"

typedef unsigned char byte_t;

const char* byte_to_binary( uint8_t x )
{
    static char b[ CHAR_BIT + 1 ];
    b[0] = '\0';

    for( uint16_t z = SCHAR_MAX + 1; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}


void scramble_string( const char* restrict key, char* restrict string, size_t len, unsigned short pivot )
{
	long string_len = len;
	size_t key_len  = strlen( key );

	while( string_len >= 0 )
	{
		string[ string_len ] = (string[ string_len ] + pivot) % 256;
		string[ string_len ] = (byte_t) ( string[string_len] ^ key[string_len % key_len] );
		string_len--;
	}
}

void unscramble_string( const char* restrict key, char* restrict string, size_t len, unsigned short pivot )
{
	long string_len = len; 
	size_t key_len  = strlen( key );

	while( string_len >= 0 )
	{
		string[ string_len ] = (byte_t) ( string[string_len] ^ key[string_len % key_len] );
		string[ string_len ] = (string[ string_len ] - pivot) % 256;
		string_len--;
	}
}



void random_string( random_string_type_t type, char* string, size_t length )
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
	max = strlen( pool ) + 1;


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

const char* ordinal_string( long number )
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



void xor_bytes( const void* restrict a, size_t a_size, const void* restrict b, size_t b_size, void* restrict result )
{
	const byte_t* p_a = a;
	const byte_t* p_b = b;
	byte_t* p_r       = result;
	long i            = b_size;


	while( i >= 0 )
	{
		p_r[ i ] = (byte_t) ( p_b[i] ^ p_a[i % (a_size + 1)] );
		i--;
	}
}

void swap( void* restrict left, void* restrict right, size_t size )
{
	unsigned char tmp[ size ];

	memcpy( tmp, left, size );
	memcpy( left, right, size );
	memcpy( right, tmp, size );
}


