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
#include <stdlib.h>
#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS
#endif
#include "xtd/floating-point.h"
#include "xtd/test.h"

static bool test_float_is_equal(test_ctx_t* ctx)
{
    bool result = true;

    if (!test_assert_true(ctx, float_is_equal(1 / 3.0f, 0.33333333333f), "Expecting floats to be equal"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_true(ctx, float_is_equal(0.0f, (10 / 5.0f) - 1.999999999999999f), "Expecting floats to be equal"))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_double_is_equal(test_ctx_t* ctx)
{
    bool result = true;

    double a  = 1 / 3.0;
    double b  = 0.3333333333333333333333;
    if (!test_assert_true(ctx, double_is_equal(a, b), "Expecting %lf and %lf to be equal", a, b))
    {
        result = false;
        goto done;
    }

    a = 0.0;
    b = (10 / 5.0) - 1.999999999999999999;
    if (!test_assert_true(ctx, double_is_equal(a, b), "Expecting %lf and %lf to be equal", a, b))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

static bool test_long_double_is_equal(test_ctx_t* ctx)
{
    bool result = true;

    long double a  = 1 / 3.0L;
    long double b  = 0.33333333333333333333L;
    if (!test_assert_true(ctx, long_double_is_equal(a, b), "Expecting %lf and %lf to be equal", a, b))
    {
        result = false;
        goto done;
    }

    a  = (10 / 5.0L) - 1.99999999999999999999L;
    b  = 0.0L;
    if (!test_assert_true(ctx, long_double_is_equal(a, b), "Expecting %lf and %lf to be equal", a, b))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

const char* FLOATING_POINT_TEST_DESCRIPTION = "Testing functions in <xtd/floating-point.h>";
const test_case_t FLOATING_POINT_TEST_CASES[] = {
    { "Test float_is_equal()", test_float_is_equal },
    { "Test double_is_equal()", test_double_is_equal },
    { "Test long_double_is_equal()", test_long_double_is_equal },
};
const size_t FLOATING_POINT_TEST_COUNT = sizeof(FLOATING_POINT_TEST_CASES) / sizeof(FLOATING_POINT_TEST_CASES[0]);

#ifdef TEST_FLOATING_POINT
int main(int argc, char* argv[])
{
    size_t pass_count = test_features(FLOATING_POINT_TEST_DESCRIPTION, FLOATING_POINT_TEST_CASES, FLOATING_POINT_TEST_COUNT, true);
    return FLOATING_POINT_TEST_COUNT - pass_count;
}
#endif
