#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

double time_seconds(void)
{
    struct timeval now;

    if (gettimeofday(&now, NULL) < 0)
    {
        return 0.0;
    }

    return now.tv_sec + (now.tv_usec / 1000000.0);
}

double time_milliseconds(void)
{
    struct timeval now;

    if (gettimeofday(&now, NULL) < 0)
    {
        return 0.0;
    }

    return 1000 * now.tv_sec + (now.tv_usec / 1000.0);
}

void time_msleep(int milliseconds)
{
    usleep(1000 * milliseconds);
}

double time_utc_offset(const char* iana_tz /* i.e. America/New_York */) /* not thread safe */
{
    assert(iana_tz);
    const char* existing_tz = getenv("TZ");

    setenv("TZ", iana_tz, 1);
    tzset(); // Initializes global timezone variable

    double utc_offset = -(timezone / 3600.0);

    if (existing_tz)
    {
        setenv("TZ", existing_tz, 1);
        tzset(); // Not sure if this is needed but it's safer.
    }

    return utc_offset;
}

struct tm* time_local(time_t t, const char* iana_tz /* i.e. America/New_York */) /* not thread safe */
{
    const char* existing_tz = getenv("TZ");

    setenv("TZ", iana_tz, 1);
    tzset(); // Initializes global timezone variable

    struct tm* tm = localtime(&t);

    if (existing_tz)
    {
        setenv("TZ", existing_tz, 1);
        tzset(); // Not sure if this is needed but it's safer.
    }

    return tm;
}

