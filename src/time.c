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
#include <stdint.h>
#include "xtd/time.h"

uint64_t time_secs( void )
{
    return (uint64_t) time_seconds( );
}

uint64_t time_msecs( void )
{
    return (uint64_t) time_milliseconds( );
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

    if ( size < sizeof("YYYY-MM-DDTHH:MM:SSZ") )
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
    if ( size < sizeof("YYYY-MM-DDTHH:MM:SS.sssZ") )
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
