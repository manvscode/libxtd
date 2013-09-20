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
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>
#include "mime.h"


typedef struct tag_mime_record {
	char *mime_type;
	char *extension;
} mime_record;

int mime_record_compare( const void *a, const void *b );

/*
 * String helpers
 */
static char *strtrim_left( char *string );
static char *strtrim_right( char *string );


boolean mime_record_destroy( void *element );



boolean mime_create( mime_table_t *p_table )
{
	assert( p_table );
	return mime_create_from_file( p_table, "/etc/mime.types" );
}

boolean mime_create_from_file( mime_table_t *p_table, const char *s_mime_file )
{
	char buffer[ 128 ];
	FILE *f = NULL;

	assert( p_table );

	vector_create( p_table, sizeof(mime_record), 128, mime_record_destroy, malloc, free );

	f = fopen( s_mime_file, "rb" );

	if( !f )
	{
		return FALSE;
	}

	while( !feof(f) )
	{
		fgets( buffer, sizeof(buffer), f );

		char *trimmed = strtrim_right( strtrim_left( buffer ) );
		if( *trimmed == '#' ) continue;


		int token_count = 0;
		char *mime_type = NULL;
		char *token     = strtok( buffer, "\t\n\r " );

		while( token )
		{
			if( token_count == 0 )
			{
				mime_type = token;
			}
			else
			{
				mime_record record;

				record.mime_type = strndup( mime_type, sizeof(buffer) );
				record.extension = strndup( token, sizeof(buffer) );

				vector_push( p_table, &record );
			}

			token_count += 1;
			token        = strtok( NULL, "\t\n\r " );
		}
	}

	/* sort the table */
	qsort( vector_array(p_table), vector_size(p_table), sizeof(mime_record), mime_record_compare );

	return TRUE;
}

void mime_destroy( mime_table_t *p_table )
{
	vector_destroy( p_table );
}

boolean mime_record_destroy( void *element )
{
	assert( element );

	mime_record *p_record = (mime_record *) element;
	free( p_record->extension );
	free( p_record->mime_type );
	return TRUE;
}

void mime_debug_table( const mime_table_t *p_table )
{
	int i;
	assert( p_table );

	for( i = 0; i < vector_size(p_table); i++ )
	{
		mime_record *p_record = (mime_record *) vector_get( (mime_table_t*) p_table, i );
		printf( "%20s --> %s\n", p_record->extension, p_record->mime_type );
	}

	printf( "     ===============================================\n" );
	printf( "                   # of records: %zu\n", vector_size(p_table) );
}

const char *mime_type( const mime_table_t *p_table, const char *extension )
{
	mime_record key;
	mime_record *p_record = NULL;

	assert( p_table );
	key.extension = (char *) extension;

	p_record = (mime_record *) bsearch( &key, vector_array(p_table), vector_size(p_table), sizeof(mime_record), mime_record_compare );

	return p_record ? (const char *) p_record->mime_type : NULL;
}

int mime_record_compare( const void *a, const void *b )
{
	assert( a && b );
	return strcasecmp( ((mime_record*) a)->extension, ((mime_record*) b)->extension );
}


/*
 * String helpers
 */
char *strtrim_left( char *string )
{
	char *first_char = string;

	while( *first_char )
	{
		if( isspace( *first_char) )
		{
			first_char++;
		}
		else
		{
			break;
		}
	}

	return first_char;
}

char *strtrim_right( char *string )
{
    int len = strlen( string );
    char *end;

    while ( *string && len)
	{
        end = string + len - 1;

        if( isspace(*end) )
		{
            *end = 0;
		}
        else
		{
            break;
		}

        len = strlen(string);
    }

    return string;
}


