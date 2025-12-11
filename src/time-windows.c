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
