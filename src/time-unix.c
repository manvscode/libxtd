#include <stdlib.h>
#include <sys/time.h>

double time_seconds( void )
{
	struct timeval now;

	if( gettimeofday( &now, NULL ) < 0 )
	{
		return 0.0;
	}

	return now.tv_sec + (now.tv_usec / 1000000.0);
}

double time_milliseconds( void )
{
	struct timeval now;

	if( gettimeofday( &now, NULL ) < 0 )
	{
		return 0.0;
	}

	return 1000 * now.tv_sec + (now.tv_usec / 1000.0);
}
