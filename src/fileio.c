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
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <dirent.h>
#include <sys/stat.h>
#include "utility.h"

bool file_exists( const char* path )
{
	return access( path, F_OK ) == 0;
}

bool file_is_writeable( const char* path )
{
	return access( path, W_OK ) == 0;
}

bool file_is_readable( const char* path )
{
	return access( path, R_OK ) == 0;
}

bool file_is_executable( const char* path )
{
	return access( path, X_OK ) == 0;
}

bool file_copy( const char* restrict src_path, const char* restrict dst_path )
{
	FILE* src_file = NULL;
	FILE* dst_file = NULL;
	char buffer[ 4096 ];

	src_file = fopen( src_path, "rb" );

	if( !src_path )
	{
		return 0;
	}

	dst_file = fopen( dst_path, "wb" );

	if( !dst_path )
	{
		return 0;
	}

	while( !feof( src_file ) )
	{
    	size_t bytes_read    = fread( buffer, sizeof(char), sizeof(buffer), src_file );
		size_t bytes_written = 0;

		while( bytes_read - bytes_written > 0 )
		{
			bytes_written += fwrite( buffer + bytes_written, sizeof(char), bytes_read - bytes_written, dst_file );
		}
	}

	fclose( src_file );
	fclose( dst_file );

	return 1;
}

bool file_delete( const char* path )
{
	if( is_dir(path) )
	{
		DIR* d = opendir( path );
		int result = 1;

		if( d )
		{
			struct dirent* p_file = readdir( d );
			result &= file_delete( p_file->d_name );
		}

		closedir( d );
		return result;
	}
	else
	{
		return unlink( path ) == 0;
	}
}

long long file_size( const char* path )
{
    struct stat s;

    if( stat( path, &s ) == 0 )
	{
        return s.st_size;
    }

	return 0L;
}

long file_age( const char* path ) // Return age of file in seconds. -1 = doesnt exist or error
{
    struct stat s;

    if( stat( path, &s ) == 0 )
	{
    	return time(NULL) - s.st_mtime;
    }

	return -1;
}

const char* file_basename( const char* filename )
{
	const char *base = filename;

	while( *filename )
	{
		if( *filename++ == '/' )
		{
			base = filename;
		}
	}

	return base;
}

const char* file_extension( const char* filename )
{
	const char* extension = strrchr( filename, '.' );

	if( !extension )
	{
		return NULL;
	}
	else
	{
		extension += 1;

		if( !extension )
		{
			return NULL;
		}
	}

	return extension;
}

char* file_load_contents( const char* path, size_t *size )
{
	FILE* file = fopen( path, "r" );
	char* result = NULL;

	if( file )
	{
		fseek( file, 0, SEEK_END );
		size_t file_size = ftell( file ); /* TODO: what if size is 0 */
		fseek( file, 0, SEEK_SET );

		if( file_size > 0 )
		{
			*size = file_size + 1;
			result = (char*) malloc( sizeof(char) * (*size) );

			if( result )
			{
				char* buffer = result;
				long sz      = file_size;

				while( !feof( file ) && sz > 0 )
				{
					size_t bytes_read = fread( buffer, sizeof(char), sz, file );
					buffer += bytes_read;
					sz   -= bytes_read;
				}

				result[ *size - 1 ] = '\0';
			}
		}

		fclose( file );
	}

	return result;
}

bool is_file( const char* path )
{
	struct stat s;

	if( stat( path, &s ) == 0 )
	{
		return S_ISREG( s.st_mode );
	}

	return 0;
}

bool is_dir( const char* path )
{
    struct stat s;

    if( stat( path, &s) == 0 )
	{
        return S_ISDIR(s.st_mode);
    }

	return 0;
}


int readline( char *buf, size_t size, FILE *stream )
{
    if( fgets( buf, size, stream ) == NULL )
	{
        return EOF;
    }

    char *n = strchr( buf, '\n' );

    if( n )
	{
        *n = '\0';
        /* A line was read successfully without truncation. */
    }
	else
	{
        int c;
        while( (c = getchar()) != EOF && c != '\n');
        if( c == EOF )
		{
            return EOF;
        }
        /* A line was read successfully but was truncated. */
    }

    return 0;
}
