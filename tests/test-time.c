/*
 * Copyright (C) 2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#include <stdio.h>
#include <string.h>
#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
#include <time.h>
#include "xtd/time.h"
#include "xtd/test.h"

#define SLEEP_S  (2)
#define SLEEP_MS (SLEEP_S * 1000)

static bool test_time_seconds(test_ctx_t* ctx)
{
    bool result = true;
    double start = time_seconds();
    time_msleep(SLEEP_MS);
    double end = time_seconds();

    if (!test_assert_equals(ctx, SLEEP_S, (int)(end - start), "Expected elapsed time to be %d seconds", SLEEP_S))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_milliseconds(test_ctx_t* ctx)
{
    bool result = true;
    double start = time_milliseconds();
    time_msleep(SLEEP_MS);
    double end = time_milliseconds();

    if (!test_assert_equals(ctx, SLEEP_MS, (int)(end - start), "Expected elapsed time to be %d milliseconds", SLEEP_MS))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_secs(test_ctx_t* ctx)
{
    bool result = true;
    uint64_t start = time_secs();
    time_msleep(SLEEP_MS);
    uint64_t end = time_secs();

    if (!test_assert_equals(ctx, SLEEP_S, (int)(end - start), "Expected elapsed time to be %d seconds", SLEEP_S))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_msecs(test_ctx_t* ctx)
{
    bool result = true;
    uint64_t start = time_msecs();
    time_msleep(SLEEP_MS);
    uint64_t end = time_msecs();

    if (!test_assert_equals(ctx, (unsigned long)SLEEP_MS, (unsigned long)(end - start), "Expected elapsed time to be %d milliseconds", SLEEP_MS))
    {
        result = false;
        goto done;
    }

done:
    return result;
}


static bool test_time_msleep(test_ctx_t* ctx)
{
    bool result = true;
    double start = time_milliseconds();
    time_msleep(SLEEP_MS);
    double end = time_milliseconds();

    if (!test_assert_equals(ctx, (unsigned long) SLEEP_MS, (unsigned long)(end - start), "Expected elapsed time to be %ld milliseconds", SLEEP_MS))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_iso8601(test_ctx_t* ctx)
{
    bool result = true;
    const char* actual = time_iso8601(1590989950);
    const char* expected = "2020-06-01T05:39:10Z";

    if (!test_assert_equals(ctx, expected, actual, "Expected elapsed time to be %s", expected))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_iso8601_r(test_ctx_t* ctx)
{
    bool result = true;
    char actual[32];
    bool time_result = time_iso8601_r(1590989950, actual, sizeof(actual));
    const char* expected = "2020-06-01T05:39:10Z";

    if (!test_assert_true(ctx, time_result, "Expected function to succeed"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, expected, actual, "Expected elapsed time to be %s", expected))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_iso8601_precision(test_ctx_t* ctx)
{
    bool result = true;
    const char* actual = time_iso8601_precision(1590989950, 239);
    const char* expected = "2020-06-01T05:39:10.239Z";

    if (!test_assert_equals(ctx, expected, actual, "Expected elapsed time to be %s", expected))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_iso8601_precision_r(test_ctx_t* ctx)
{
    bool result = true;
    char actual[32];
    bool time_result = time_iso8601_precision_r(1590989950, 567, actual, sizeof(actual));
    const char* expected = "2020-06-01T05:39:10.567Z";

    if (!test_assert_true(ctx, time_result, "Expected function to succeed"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, expected, actual, "Expected elapsed time to be %s", expected))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_utf_offset(test_ctx_t* ctx)
{
    bool result = true;
    const char* timezone = "America/New_York";
    double actual = time_utc_offset(timezone);

    double expected = -5.0;

    if (!test_assert_equals(ctx, expected, actual, "Expected UTC offset for %s to be %lf", timezone, expected))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_time_local(test_ctx_t* ctx)
{
    bool result = true;
    const char* timezone = "America/New_York";
    struct tm* tm = time_local(1590989950, timezone); // Mon Jun 1 01:39:10 2020

    if (!test_assert_not_null(ctx, tm, "Expected function to not return NULL"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 1, tm->tm_isdst, "Expected daylight saving time"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 152, tm->tm_yday, "Expected day of the year to be 152"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 1, tm->tm_wday, "Expected day of the week to be 1"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 2020 - 1900, tm->tm_year, "Expected year to be 120"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 5, tm->tm_mon, "Expected month to be 5"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 1, tm->tm_mday, "Expected day of the month to be 1"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 1, tm->tm_hour, "Expected hour to be 1"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 39, tm->tm_min, "Expected minutes to be 39"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, 10, tm->tm_sec, "Expected seconds to be 10"))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

const char* TIME_TEST_DESCRIPTION = "Testing functions in <xtd/time.h>";
const test_case_t TIME_TEST_CASES[] = {
    { "Test time_seconds()", test_time_seconds },
    { "Test time_milliseconds()", test_time_milliseconds },
    { "Test time_secs()", test_time_secs },
    { "Test time_msecs()", test_time_msecs },
    { "Test time_msleep()", test_time_msleep },
    { "Test time_iso8601()", test_time_iso8601 },
    { "Test time_iso8601_r()", test_time_iso8601_r },
    { "Test time_iso8601_precision()", test_time_iso8601_precision },
    { "Test time_iso8601_precision_r()", test_time_iso8601_precision_r },
    { "Test time_utc_offset()", test_time_utf_offset },
    { "Test time_local()", test_time_local },
};
const size_t TIME_TEST_COUNT = sizeof(TIME_TEST_CASES) / sizeof(TIME_TEST_CASES[0]);

#ifdef TEST_TIME
int main(int argc, char* argv[])
{
    size_t pass_count = test_features(TIME_TEST_DESCRIPTION, TIME_TEST_CASES, TIME_TEST_COUNT, true);
    return TIME_TEST_COUNT - pass_count;
}
#endif
