#include <stdlib.h>
#include <windows.h>

double time_seconds( void )
{
	LARGE_INTEGER time;
	LARGE_INTEGER frequency;

	QueryPerformanceFrequency( &frequency );
	QueryPerformanceCounter( &time );

	time.QuadPart /= frequency.QuadPart;
	//return time.QuadPart / 1000000.0;
	return (double) time.QuadPart;
}

double time_milliseconds( void )
{
	LARGE_INTEGER time;
	LARGE_INTEGER frequency;

	QueryPerformanceFrequency( &frequency );
	QueryPerformanceCounter( &time );

	time.QuadPart /= frequency.QuadPart;
	return time.QuadPart * 1000.0;
}

void time_msleep( int milliseconds )
{
	Sleep( milliseconds );
}
