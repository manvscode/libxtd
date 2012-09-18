#include <stdio.h>
#include "exceptions.h"

typedef enum errors {
	ERR_NONE = 0,
	ERR_BAD_FILE
} errors_t;


int main( int argc, char *argv[] )
{
	exception_t ex = exception_create( );

	printf( "Attempting to open a file.\n" );

	exception_try( ex )
	{
		FILE *file = fopen( "this-file-does-not-exist.txt", "r" );

		if( !file )
		{
			exception_throw( ex, ERR_BAD_FILE );
		}

		printf( "This code is not reachable." );
		fclose( file );
	}
	exception_catch( ex, ERR_BAD_FILE )
	{
		printf( "ERR_BAD_FILE exception was caught.\n" );
	}

	exception_destroy( &ex );

	return 0;
}
