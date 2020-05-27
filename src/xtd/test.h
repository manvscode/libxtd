/*
 * Copyright (C) 2010-2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#ifndef _TEST_H_
#define _TEST_H_

#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <xtd/time.h>
#include <xtd/floating-point.h>

#define COLOR_BEGIN(bg,fg)                    "\e[" #bg ";" #fg "m"
#define COLOR_END                             "\e[m"
#define COLOR_TOKEN(color_bg, color_fg, tok)  COLOR_BEGIN(color_bg, color_fg) #tok COLOR_END
#define COLOR_STRING(color_bg, color_fg, str) COLOR_BEGIN(color_bg, color_fg) str COLOR_END

#define COLOR_GREEN                           COLOR_BEGIN(0,32)
#define COLOR_RED                             COLOR_BEGIN(0,31)
#define COLOR_YELLOW                          COLOR_BEGIN(0,33)
#define COLOR_BLUE                            COLOR_BEGIN(0,34)
#define COLOR_MAGENTA                         COLOR_BEGIN(0,35)
#define COLOR_CYAN                            COLOR_BEGIN(0,36)
#define COLOR_WHITE                           COLOR_BEGIN(0,37)

#define COLOR_GREEN_STR(s)                    COLOR_STRING(0,32,s)
#define COLOR_YELLOW_STR(s)                   COLOR_STRING(0,33,s)
#define COLOR_RED_STR(s)                      COLOR_STRING(0,31,s)
#define COLOR_CYAN_STR(s)                     COLOR_STRING(0,36,s)

typedef bool   (*test_fxn)      ( void );
typedef size_t (*test_size_fxn) ( void );

static inline bool test_nil( void ) { return false; }

static inline bool integer_equals( long a, long b )
{
	return a == b;
}

static inline bool test_float_equals( float a, float b )
{
	return float_is_equal( a, b );
}

static inline bool test_double_equals( double a, double b )
{
	return double_is_equal( a, b );
}

static inline bool test_long_double_equals( long double a, long double b )
{
	return long_double_is_equal( a, b );
}

static inline void test_wait_for_true(const bool* flag, int timeout)
{
	double start = time_milliseconds();
	double elapsed = 0.0;

	while (!*flag && elapsed < timeout)
	{
		time_msleep(10);
		elapsed = time_milliseconds() - start;
	}
}

static inline void test_wait_for_int(const int* n, int value, int timeout)
{
	double start = time_milliseconds();
	double elapsed = 0.0;

	while (*n != value && elapsed < timeout)
	{
		time_msleep(10);
		elapsed = time_milliseconds() - start;
	}
}

static inline bool test_feature( unsigned int i, const char* feature, test_fxn test )
{
	bool is_passed = test();
	printf( "%s%5u%s: %s... %s\n", COLOR_CYAN, i, COLOR_END, feature, is_passed ? COLOR_GREEN_STR("ok") : COLOR_RED_STR("failed") );
	return is_passed;
}

typedef struct test_feature {
	const char* feature;
	test_fxn    function;
} test_feature_t;



static inline bool test_features( const char* suite, const test_feature_t features[], size_t count )
{
	bool is_passed = true;

	size_t len = strlen(suite);
	size_t half_len = len / 2;
	int w = 10;
	printf( "%s: %s%-30s%s\n", COLOR_CYAN_STR("Suite"), COLOR_YELLOW, suite, COLOR_END );
	for( size_t i = 0; is_passed && i < count; i++ )
	{
		is_passed = test_feature( i + 1, features[ i ].feature, features[ i ].function );
	}

	printf( "----------------------\n" );
	printf( "%sOverall%s: %s\n\n", COLOR_CYAN, COLOR_END, is_passed ? COLOR_GREEN_STR("PASSED.") : COLOR_RED_STR("FAILED.") );

	return is_passed;
}


typedef struct test_suite {
	const char* suite;
	const test_feature_t* features;
	test_size_fxn count;
} test_suite_t;

static inline bool test_suites( const test_suite_t suites[], size_t count )
{
	bool is_passed = true;

	for( size_t i = 0; is_passed && i < count; i++ )
	{
		size_t feature_count = suites[ i ].count();
		is_passed = test_features( suites[ i ].suite, suites[ i ].features, feature_count );
	}

	printf( "\n" );

	if( is_passed )
	{
		printf( "%sAll Suites%s: %s\n\n", COLOR_CYAN, COLOR_END, COLOR_GREEN_STR("PASSED.") );
	}
	else
	{
		printf( "%sOne or more suites have%s: %s\n\n", COLOR_CYAN, COLOR_END, COLOR_RED_STR("FAILED.") );
	}

	return is_passed;
}

#endif /* _TEST_H_ */
