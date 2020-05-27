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
#include "xtd/filesystem.h"

#ifndef MAX_PATH
# define MAX_PATH   256
#endif

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
	bool result = false;

	if( is_file(path) )
	{
		result = (unlink( path ) == 0);
	}

	return result;
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
		result = mkpath( path, 0700 ) == 0;
	}

	return result;
}

bool directory_delete( const char* path, bool recursive )
{
	bool result = true;

	if( is_directory(path) )
	{
		if( recursive )
		{
			DIR* d = opendir( path );
			int result = 1;

			for( struct dirent* entry = readdir( d );
			     entry && result;
			     entry = readdir( d ) )
			{
				if( strcmp(entry->d_name, ".") == 0 ) continue;
				else if( strcmp(entry->d_name, "..") == 0 ) continue;

				bool is_dir = entry->d_type & DT_DIR;

				char absolute_path[ MAX_PATH + 1 ];
				snprintf( absolute_path, sizeof(absolute_path), "%s/%s", path, entry->d_name );
				absolute_path[ sizeof(absolute_path) - 1 ] = '\0';

				if( is_dir )
				{
					result = directory_delete( absolute_path, recursive );
				}
				else
				{
					result = (unlink( absolute_path ) == 0);
				}
			} // for

			closedir( d );
		} // if recursive

		result = result && (rmdir( path ) == 0);
	} // if

	return result;
}

int mkpath( const char *s, mode_t mode )
{
	int result = -1;
	char* path = NULL;

	if( strcmp( s, "/" ) == 0 ||
	    strcmp( s, "." ) == 0 )
	{
		result = 0;
		goto done;
	}

	path = directory_path( s );

	if( !path )
	{
		goto done;
	}

	if( mkpath( path, mode ) < 0 )
	{
		goto done;
	}

	if( mkdir( s, mode ) == -1 && errno != EEXIST )
	{
		result = -1;
	}
	else
	{
		result = 0;
	}

done:
	free( path );
	return result;
}

extern char* __path_r( const char* path, char dir_separator, char* buffer, size_t size ); /* returns NULL on error  */
extern char* __path( const char* path, char dir_separator ); /* allocates memory */

char* directory_path_r( const char* _path, char* buffer, size_t size )
{
	assert( _path );
	return __path_r( _path, '/', buffer, size );
}

char* directory_path( const char* _path ) /* allocates memory */
{
	assert( _path );
	return __path( _path, '/' );
}

static void __directory_enumerate( const char* path, bool recursive, directory_enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args );

void directory_enumerate( const char* path, bool recursive, directory_enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args )
{
	if( path )
	{
		size_t len = strlen( path );
		bool ends_with_slash = len > 0 && path[ len - 1 ] == '/';
		size_t sz = ends_with_slash ? len : (len + 1);

		char path_no_trailing_slash[ MAX_PATH + 1];
		strncpy( path_no_trailing_slash, path, sz );
		path_no_trailing_slash[ sz - 1 ] = '\0';

		__directory_enumerate( path_no_trailing_slash, recursive, mode, process_file, args );
	}
}

void __directory_enumerate( const char* path, bool recursive, directory_enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args )
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

			char absolute_path[ MAX_PATH + 1 ];
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

