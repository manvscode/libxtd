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
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
# include <stdint.h>
#else
# error "Need a C99 compiler."
#endif
#include <stdlib.h>
#include <stdbool.h>

/*
 * This is a generic function that can be used for testing equality between
 * many different data-types.
 */
#define test_assert_equals(ctx, expected, actual, ... ) \
	_Generic((expected), \
	         const void*: test_assert_pointer_equals, \
	               void*: test_assert_pointer_equals, \
	         const char*: test_assert_string_equals, \
	               char*: test_assert_string_equals, \
	         long double: test_assert_long_double_equals, \
	              double: test_assert_double_equals, \
	               float: test_assert_float_equals, \
	       unsigned long: test_assert_unsigned_long_equals, \
	                long: test_assert_long_equals, \
	        unsigned int: test_assert_unsigned_int_equals, \
	                 int: test_assert_int_equals, \
	      unsigned short: test_assert_unsigned_short_equals, \
	               short: test_assert_short_equals, \
	       unsigned char: test_assert_unsigned_char_equals, \
	                char: test_assert_char_equals \
	)(ctx, expected, actual, __VA_ARGS__)

/*
 * This function will loop and test a boolean flag until it becomes true.
 */
void test_wait_for_true(const bool* flag, int timeout);

/*
 * This function will loop and test a integer flag until it becomes true.
 */
void test_wait_for_int(const int* n, int value, int timeout);

/*
 * This is the internal context passed to each test case.
 */
struct test_ctx;
typedef struct test_ctx test_ctx_t;

/*
 * This is the function signature that all unit tests should follow.
 */
typedef bool (*test_fxn_t) ( test_ctx_t* ctx );

/*
 * This is a convenience for an empty unit test.
 */
bool test_nil( test_ctx_t* ctx );

/*
 * This structure describes a unit
 */
typedef struct test_case {
	const char* description;
	test_fxn_t test;
} test_case_t;

/*
 * This function will run a group of test cases.
 */
size_t test_features( const char* description, const test_case_t cases[], size_t count, bool continue_on_failure );

/*
 * This is the signature for a function that returns a description for the
 * test suite.
 */
typedef const char* (*test_case_description_fxn_t) ( void );

/*
 * This is the signature for a function that knows how many test cases (see
 * test_case_t) are in a test suite.
 */
typedef size_t (*test_case_count_fxn_t) ( void );

/*
 * This is the signature for a function that returns the a pointer to an
 * array of test cases for the test suite.
 */
typedef const test_case_t* (*test_case_fxn_t) ( void );

/*
 * This structure describes a grouping of test cases, also called a test suite.
 */
typedef struct test_suite {
	test_case_description_fxn_t get_description;
	test_case_count_fxn_t get_count;
	test_case_fxn_t get_cases;
} test_suite_t;

/*
 * This function will run several suites of test cases.
 */
bool test_suites( const test_suite_t suites[], size_t count, size_t* p_pass_count, size_t* p_fail_count );

/*
 * Various assertions that can be used for testing functionality.
 */
bool test_assert_true( test_ctx_t* ctx, bool expression, const char* message, ... );
bool test_assert_not_null( test_ctx_t* ctx, const void* p, const char* message, ... );
bool test_assert_pointer_equals( test_ctx_t* ctx, const void* a, const void* b, const char* message, ... );
bool test_assert_memory_equals( test_ctx_t* ctx, const void* a, const void* b, size_t size, const char* message, ... );
bool test_assert_string_equals( test_ctx_t* ctx, const char* a, const char* b, const char* message, ... );
bool test_assert_char_equals( test_ctx_t* ctx, char a, char b, const char* message, ... );
bool test_assert_unsigned_char_equals( test_ctx_t* ctx, unsigned char a, unsigned char b, const char* message, ... );
bool test_assert_short_equals( test_ctx_t* ctx, short a, short b, const char* message, ... );
bool test_assert_unsigned_short_equals ( test_ctx_t* ctx, unsigned short a, unsigned short b, const char* message, ... );
bool test_assert_int_equals( test_ctx_t* ctx, int a, int b, const char* message, ... );
bool test_assert_unsigned_int_equals( test_ctx_t* ctx, unsigned int a, unsigned int b, const char* message, ... );
bool test_assert_long_equals( test_ctx_t* ctx, long a, long b, const char* message, ... );
bool test_assert_unsigned_long_equals( test_ctx_t* ctx, unsigned long a, unsigned long b, const char* message, ... );
bool test_assert_float_equals( test_ctx_t* ctx, float a, float b, const char* message, ... );
bool test_assert_double_equals( test_ctx_t* ctx, double a, double b, const char* message, ... );
bool test_assert_long_double_equals( test_ctx_t* ctx, long double a, long double b, const char* message, ... );
bool test_assert_size_equals( test_ctx_t* ctx, size_t a, size_t b, const char* message, ... );

#endif /* _TEST_H_ */
