#include "utility.h"
#include "libutility-config.h"

typedef union two_bytes {
	unsigned short s;
	unsigned char bytes[ 2 ];
} two_bytes_t;


bool is_big_endian( void )
{
	two_bytes_t check;
	check.s = 1;

	if( check.bytes[ 0 ] == 1 )
	{
		return false; /* little endian */
	}

	return true;
}

void swap_every_two_bytes( void* mem, size_t size )
{
	unsigned char* buffer = (unsigned char*) mem;

	/* If we have an odd number of bytes, then
	 * we subtract 1 and swap up until that size.
	 */
	size -= (size % 2);

	for( size_t i = 0; i < size - 1; i += 2 )
	{
		unsigned char tmp = buffer[ i ];
		buffer[ i ] = buffer[ i + 1];
		buffer[ i + 1 ] = tmp;
	}
}

#ifdef WORDS_BIGENDIAN
void hton( void *mem, size_t size )
{
	if( !is_big_endian( ) )
	{
		swap_every_two_bytes( mem, size );
	}
}

void ntoh( void *mem, size_t size )
{
	if( !is_big_endian( ) )
	{
		swap_every_two_bytes( mem, size );
	}
}
#endif
