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

const char* time_iso8601_precision( time_t t, unsigned int milliseconds )
{
	// Adjust for any extra seconds
	t += (milliseconds / 1000);
	milliseconds = (milliseconds % 1000);

	struct tm* time_tm = gmtime( &t );
	static char buf[ sizeof("YYYY-MM-DDTHH:MM:SS") ];
	static char iso_8601[ sizeof("YYYY-MM-DDTHH:MM:SS.sssZ") ];
	strftime( buf, sizeof(buf), "%FT%T", time_tm );
	snprintf(iso_8601, sizeof(iso_8601), "%s.%3uZ", buf, milliseconds );
	return iso_8601;
}
