/* Copyright (C) 2016-2025 by Joseph A. Marrero, http://www.joemarrero.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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

