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
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
//#include <libgen.h>
#include <sys/stat.h>
#include "utility.h"

static int mkpath( const char *s, mode_t mode );

bool file_exists( const char* path )
{
	assert( path );
	return access( path, F_OK ) == 0;
}

bool file_is_writeable( const char* path )
{
	assert( path );
	return access( path, W_OK ) == 0;
}

bool file_is_readable( const char* path )
{
	assert( path );
	return access( path, R_OK ) == 0;
}

bool file_is_executable( const char* path )
{
	assert( path );
	return access( path, X_OK ) == 0;
}

bool file_delete( const char* path )
{
	assert( path );

	if( is_directory(path) )
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

int64_t file_size( const char* path )
{
    struct stat s;
	assert( path );

    if( stat( path, &s ) == 0 )
	{
        return s.st_size;
    }

	return 0L;
}

int64_t file_age( const char* path ) // Return age of file in seconds. -1 = doesnt exist or error
{
    struct stat s;
	assert( path );

    if( stat( path, &s ) == 0 )
	{
    	return time(NULL) - s.st_mtime;
    }

	return -1;
}

extern const char* basename( const char* path, char dir_separator );

const char* file_basename( const char* filename )
{
	assert( filename );
	return basename( filename, '/' );
}

bool is_file( const char* path )
{
	struct stat s;
	assert( path );

	if( stat( path, &s ) == 0 )
	{
		return S_ISREG( s.st_mode );
	}

	return false;
}

bool is_directory( const char* path )
{
    struct stat s;
	assert( path );

    if( stat( path, &s ) == 0 )
	{
        return S_ISDIR(s.st_mode);
    }

	return false;
}

bool directory_exists( const char* path )
{
    struct stat s;
	assert( path );
    return stat( path, &s ) != -1;
}

bool directory_create( const char* path )
{
	bool result = false;
	assert( path );

	if( !directory_exists( path ) )
	{
		//result = mkdir( path, 0700 ) == 0;
		result = mkpath( path, 0700 ) == 0;
	}

	return result;
}


int mkpath( const char *s, mode_t mode )
{
	int result = -1;
	char* path = NULL;
	char* up   = NULL;

	if( strcmp( s, "." ) == 0 || strcmp( s, "/" ) == 0 )
	{
		return 0;
	}

	path = directory_path( s );

	if( !path )
	{
		goto done;
	}

	up = directory_path( path );

	if( !up )
	{
		goto done;
	}

	if( mkpath( up, mode ) == -1 && errno != EEXIST )
	{
		goto done;
	}

	if( mkdir( path, mode ) == -1 && errno != EEXIST )
	{
		result = -1;
	}
	else
	{
		result = 0;
	}

done:
	if( up ) free( up );
	if( path ) free( path );
	return result;
}



#ifndef MAX_PATH
#define MAX_PATH   256
#endif

#if PATH_REENTRANT
extern char* path( const char* path, char dir_separator, char* buffer, size_t size );
#else
extern char* path( const char* path, char dir_separator );
#endif

char* directory_path( const char* _path )
{
	assert( _path );
	#if PATH_REENTRANT
	static char buffer[ MAX_PATH ];
	return path( _path, '/', buffer, MAX_PATH );
	#else
	return path( _path, '/' );
	#endif
}

static void __directory_enumerate( const char* path, bool recursive, enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args );

void directory_enumerate( const char* path, bool recursive, enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args )
{
	if( path )
	{
		size_t len = strlen( path );
		bool ends_with_slash = len > 0 && path[ len - 1 ] == '/';
		size_t sz = ends_with_slash ? len : (len + 1);

		char path_no_trailing_slash[ MAX_PATH ];
		strncpy( path_no_trailing_slash, path, sz );
		path_no_trailing_slash[ sz - 1 ] = '\0';

		__directory_enumerate( path_no_trailing_slash, recursive, mode, process_file, args );
	}
}

void __directory_enumerate( const char* path, bool recursive, enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args )
{
	DIR* dir = opendir( path );

	if( dir )
	{
		/* print all the files and directories within directory */
		for( struct dirent* ent = readdir( dir ); ent != NULL; ent = readdir( dir ) )
		{
			if( strcmp(ent->d_name, ".") == 0 ) continue;
			else if( strcmp(ent->d_name, "..") == 0 ) continue;

			bool is_dir = ent->d_type & DT_DIR;

			char absolute_path[ MAX_PATH ];
			snprintf( absolute_path, sizeof(absolute_path), "%s/%s", path, ent->d_name );
			absolute_path[ sizeof(absolute_path) - 1 ] = '\0';

			if( mode == ENUMERATE_FILES && is_dir )
			{
				// Ignore this.
			}
			else if( mode == ENUMERATE_DIRECTORIES && !is_dir )
			{
				// Ignore this.
			}
			else
			{
				process_file( absolute_path, args );
			}

			if( recursive && is_dir )
			{
				__directory_enumerate( absolute_path, recursive, mode, process_file, args );
			}
		}

		closedir( dir );
	}
}

