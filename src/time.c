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

const char* time_iso8601( time_t t )
{
	struct tm* time_tm = gmtime( &t );
	static char iso_8601[ sizeof("YYYY-MM-DDTHH:MM:SSZ") ];
	strftime( iso_8601, sizeof(iso_8601), "%FT%TZ", time_tm );
	return iso_8601;
}

bool time_iso8601_r( time_t t, char* iso_8601, size_t size )
{
	struct tm* time_tm = gmtime( &t );

	if( size < sizeof("YYYY-MM-DDTHH:MM:SSZ") )
	{
		return false;
	}

	return strftime( iso_8601, size, "%FT%TZ", time_tm ) > 0;
}

const char* time_iso8601_precision( time_t t, unsigned int milliseconds )
{
	// Adjust for any extra seconds
	t += (milliseconds / 1000);
	milliseconds = (milliseconds % 1000);

	struct tm* time_tm = gmtime( &t );
	char buf[ sizeof("YYYY-MM-DDTHH:MM:SS") ];
	strftime( buf, sizeof(buf), "%FT%T", time_tm );

	static char iso_8601[ sizeof("YYYY-MM-DDTHH:MM:SS.sssZ") ];
	snprintf(iso_8601, sizeof(iso_8601), "%s.%3uZ", buf, milliseconds );
	return iso_8601;
}

bool time_iso8601_precision_r( time_t t, unsigned int milliseconds, char* iso_8601, size_t size )
{
	if( size < sizeof("YYYY-MM-DDTHH:MM:SS.sssZ") )
	{
		return false;
	}

	// Adjust for any extra seconds
	t += (milliseconds / 1000);
	milliseconds = (milliseconds % 1000);

	struct tm* time_tm = gmtime( &t );
	char buf[ sizeof("YYYY-MM-DDTHH:MM:SS") ];
	strftime( buf, sizeof(buf), "%FT%T", time_tm );

	return snprintf(iso_8601, size, "%s.%3uZ", buf, milliseconds ) > 0;
}
