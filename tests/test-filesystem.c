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
#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS
#endif
#include "xtd/filesystem.h"
#include "xtd/test.h"

const char* FILESYSTEM_TEST_DESCRIPTION = "Testing functions in <xtd/filesystem.h>";
const test_case_t FILESYSTEM_TEST_CASES[] = {
	{ "Test file_exists()", test_nil },
	{ "Test file_is_writeable()", test_nil },
	{ "Test file_is_readable()", test_nil },
	{ "Test file_is_executable()", test_nil },
	{ "Test file_copy()", test_nil },
	{ "Test file_delete()", test_nil },
	{ "Test file_size()", test_nil },
	{ "Test file_size_string()", test_nil },
	{ "Test file_age()", test_nil },
	{ "Test file_basename()", test_nil },
	{ "Test file_extension()", test_nil },
	{ "Test file_slurp()", test_nil },
	{ "Test file_readline()", test_nil },
	{ "Test is_file()", test_nil },
	{ "Test is_directory()", test_nil },
	{ "Test directory_exists()", test_nil },
	{ "Test directory_create()", test_nil },
	{ "Test directory_delete()", test_nil },
	{ "Test directory_path_r()", test_nil },
	{ "Test directory_path()", test_nil },
	{ "Test directory_enumerate()", test_nil },
};
const size_t FILESYSTEM_TEST_COUNT = sizeof(FILESYSTEM_TEST_CASES) / sizeof(FILESYSTEM_TEST_CASES[0]);

#ifdef TEST_FILESYSTEM
int main(int argc, char* argv[])
{
	size_t pass_count = test_features( FILESYSTEM_TEST_DESCRIPTION, FILESYSTEM_TEST_CASES, FILESYSTEM_TEST_COUNT, true );
	return FILESYSTEM_TEST_COUNT - pass_count;
}
#endif
