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
#include <assert.h>
#include <windows.h>
#include <sys/stat.h>
#include "utility.h"

bool file_exists( const char* path )
{
	bool result = true;
	assert( path );
	DWORD attributes = GetFileAttributes( path ); // from winbase.h

	if(INVALID_FILE_ATTRIBUTES == attributes)
	{
		if(attributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			result = false;
		}
		else
		{
			switch(GetLastError())
			{
				case ERROR_FILE_NOT_FOUND:
				case ERROR_PATH_NOT_FOUND:
				case ERROR_INVALID_NAME:
				case ERROR_INVALID_DRIVE:
				case ERROR_NOT_READY:
				case ERROR_INVALID_PARAMETER:
				case ERROR_BAD_PATHNAME:
				case ERROR_BAD_NETPATH:
					result = false;
					break;
				default:
					break;
			}
		}
	}

	return result;
}

bool file_is_writeable( const char* path )
{
	assert( path );
	assert( false && "Not implemented!" );
	return false;
}

bool file_is_readable( const char* path )
{
	assert( path );
	assert(false && "Not implemented!");
	return false;
}

bool file_is_executable( const char* path )
{
	assert( path );
	assert(false && "Not implemented!");
	return false;
}

bool file_delete( const char* path )
{
	assert( path );
	return DeleteFile( path );
}

int64_t file_size( const char* path )
{
	WIN32_FILE_ATTRIBUTE_DATA fad;
	assert( path );

    if( GetFileAttributesEx(path, GetFileExInfoStandard, &fad) )
	{
		LARGE_INTEGER size;
		size.HighPart = fad.nFileSizeHigh;
		size.LowPart = fad.nFileSizeLow;
		return size.QuadPart;
	}

    return -1; // error condition, could call GetLastError to find out more
}

long file_age( const char* path ) // Return age of file in seconds. -1 = doesnt exist or error
{
	assert( path );
	assert(false && "Not implemented!");
	return -1;
}

extern const char* basename( const char* path, char dir_separator );

const char* file_basename( const char* filename )
{
	assert( filename );
	return basename( filename, '\\' );
}

bool is_file( const char* path )
{
	bool result = true;
	assert( path );
	DWORD attributes = GetFileAttributes( path );

	if( attributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		result = false;
	}

	return result;
}

bool is_directory( const char* path )
{
	bool result = false;
	assert( path );
	DWORD attributes = GetFileAttributes( path );

	if( attributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		result = true;
	}

	return result;
}

bool directory_exists( const char* path )
{
	assert( path );
	assert(false && "Not implemented!");
	return false;
}

bool directory_create( const char* path )
{
	assert( path );
	return CreateDirectory(path, NULL);
}

extern char* path( const char* path, char dir_separator );

char* directory_path( const char* p )
{
	assert( p );
	return path( p, '\\' );
}
