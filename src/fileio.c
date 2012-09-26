#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "utility.h"

int file_exists( const char *path )
{
	return access( path, F_OK ) == 0;
}

int file_is_writeable( const char *path )
{
	return access( path, W_OK ) == 0;
}

int file_is_readable( const char *path )
{
	return access( path, R_OK ) == 0;
}

int file_is_executable( const char *path )
{
	return access( path, X_OK ) == 0;
}


int file_copy( const char *src_path, const char *dst_path )
{
	FILE *src_file = NULL;
	FILE *dst_file = NULL;
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

int file_delete( const char *path )
{
	if( is_dir(path) )
	{
		DIR *d = opendir( path );
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

long file_size( const char *path )
{
    struct stat s;

    if( stat( path, &s ) == 0 )
	{
        return s.st_size;
    }

	return 0L;
}

int file_age( const char *path ) // Return age of file in seconds. -1 = doesnt exist or error
{
    struct stat s;

    if( stat( path, &s ) == 0 )
	{
    	return time(NULL) - s.st_mtime;
    }

	return -1;
}

int is_file( const char *path )
{
	struct stat s;

	if( stat( path, &s ) == 0 )
	{
		return S_ISREG( s.st_mode );
	}
		
	return 0;
}

int is_dir( const char *path )
{
    struct stat s;

    if( stat( path, &s) == 0 )
	{
        return S_ISDIR(s.st_mode);
    }
	
	return 0;
}

