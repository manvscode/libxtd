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
#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS
#endif
#include "xtd/endian.h"
#include "xtd/test.h"

const char* ENDIAN_TEST_DESCRIPTION = "Testing functions in <xtd/endian.h>";
const test_case_t ENDIAN_TEST_CASES[] = {
    { "Test is_big_endian()", test_nil },
    { "Test hton()", test_nil },
    { "Test ntoh()", test_nil },
};
const size_t ENDIAN_TEST_COUNT = sizeof(ENDIAN_TEST_CASES) / sizeof(ENDIAN_TEST_CASES[0]);

#ifdef TEST_ENDIAN
int main(int argc, char* argv[])
{
    size_t pass_count = test_features(ENDIAN_TEST_DESCRIPTION, ENDIAN_TEST_CASES, ENDIAN_TEST_COUNT, true);
    return ENDIAN_TEST_COUNT - pass_count;
}
#endif
