/*
 * Copyright (C) 2010-2025 by Joseph A. Marrero. http://www.manvscode.com/
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
#ifndef _FLOATING_POINT_H_
#define _FLOATING_POINT_H_
#include <stdlib.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
#else
# error "Need a C99 compiler."
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool float_is_equal       (float a, float b);
bool double_is_equal      (double a, double b);
bool long_double_is_equal (long double a, long double b);

#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
    using ::float_is_equal;
    using ::double_is_equal;
    using ::long_double_is_equal;
} /* namespace */
#endif
#endif /* _FLOATING_POINT_H_ */
