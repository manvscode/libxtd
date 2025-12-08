#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <windows.h>

double time_seconds(void)
{
    LARGE_INTEGER time;
    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);

    time.QuadPart /= frequency.QuadPart;
    //return time.QuadPart / 1000000.0;
    return (double) time.QuadPart;
}

double time_milliseconds(void)
{
    LARGE_INTEGER time;
    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);

    time.QuadPart /= frequency.QuadPart;
    return time.QuadPart * 1000.0;
}

void time_msleep(int milliseconds)
{
    Sleep(milliseconds);
}

double time_utc_offset(const char* iana_tz)
{
    assert(iana_tz);
    const char* existing_tz = getenv("TZ");

    SetEnvironmentVariable("TZ", iana_tz);
    _tzset(); // Initializes global _timezone variable

    double utc_offset = -(_timezone / 3600.0);

    if (existing_tz)
    {
        SetEnvironmentVariable("TZ", existing_tz);
        _tzset(); // Not sure if this is needed but it's safer.
    }

    return utc_offset;
}

struct tm* time_local(time_t t, const char* iana_tz /* i.e. America/New_York */) /* not thread safe */
{
    const char* existing_tz = getenv("TZ");

    SetEnvironmentVariable("TZ", iana_tz);
    _tzset(); // Initializes global _timezone variable

    struct tm* tm = localtime(&t);

    if (existing_tz)
    {
        SetEnvironmentVariable("TZ", existing_tz);
        _tzset(); // Not sure if this is needed but it's safer.
    }

    return tm;
}
