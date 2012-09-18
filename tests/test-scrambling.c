#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utility.h"


int main( int argc, char *argv[] )
{
	char SEED[ 32 ];
	char text[ 512 ];
	size_t len;
	size_t i;
	srand( time(NULL) );


	random_string( 0, SEED, sizeof(SEED) - 1 );
	SEED[ sizeof(SEED) - 1 ] = '\0';

	strcpy( text, "Joseph Marrero is an awesome computer programmer." );
	len = strlen(text);

	text[ sizeof(text) - 1 ] = '\0';

	unsigned short pivot = rand();	
	

	scramble_string( SEED, text, len, pivot );
	text[ sizeof(text) - 1 ] = '\0';
	printf( "      Pivot = [%d]\n", pivot );
	printf( "       SEED = [%s]\n", SEED );
	printf( "  Scrambled = [%s]\n", text );
	printf( "  Scrambled = [" );

	for( i = 0; i < len; i++ )
	{
		printf( "%02x", text[i] );
	}
	printf( "]\n" );

	unscramble_string( SEED, text, len, pivot );
	text[ sizeof(text) - 1 ] = '\0';
	printf( "Unscrambled = [%s]\n", text );
	printf( "Unscrambled = [" );
	for( i = 0; i < len; i++ )
	{
		printf( "%02x", text[i] );
	}
	printf( "]\n" );

	return 0;
}
