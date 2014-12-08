#include <stdint.h>
#include "utility.h"

uint64_t time_secs( void )
{
	return (uint64_t) time_seconds( );
}

uint64_t time_msecs( void )
{
	return (uint64_t) time_seconds( );
}

