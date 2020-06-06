/*
 * Copyright (C) 2010 by Joseph A. Marrero. http://www.manvscode.com/
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
#include "xtd/string.h"
#include "xtd/test.h"


extern const char* CHECKSUMS_TEST_DESCRIPTION;
extern const size_t CHECKSUMS_TEST_COUNT;
extern const test_case_t CHECKSUMS_TEST_CASES[];

static size_t checksums_test_case_count()
{
	return CHECKSUMS_TEST_COUNT;
}

static const char* checksums_test_description()
{
	return CHECKSUMS_TEST_DESCRIPTION;
}
static const test_case_t* checksums_test_cases()
{
	return CHECKSUMS_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* CMDOPT_TEST_DESCRIPTION;
extern const size_t CMDOPT_TEST_COUNT;
extern const test_case_t CMDOPT_TEST_CASES[];

static size_t cmdopt_test_case_count()
{
	return CMDOPT_TEST_COUNT;
}

static const char* cmdopt_test_description()
{
	return CMDOPT_TEST_DESCRIPTION;
}
static const test_case_t* cmdopt_test_cases()
{
	return CMDOPT_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* ENCODING_TEST_DESCRIPTION;
extern const size_t ENCODING_TEST_COUNT;
extern const test_case_t ENCODING_TEST_CASES[];

static size_t encoding_test_case_count()
{
	return ENCODING_TEST_COUNT;
}

static const char* encoding_test_description()
{
	return ENCODING_TEST_DESCRIPTION;
}
static const test_case_t* encoding_test_cases()
{
	return ENCODING_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* ENCRYPTION_TEST_DESCRIPTION;
extern const size_t ENCRYPTION_TEST_COUNT;
extern const test_case_t ENCRYPTION_TEST_CASES[];

static size_t encryption_test_case_count()
{
	return ENCRYPTION_TEST_COUNT;
}

static const char* encryption_test_description()
{
	return ENCRYPTION_TEST_DESCRIPTION;
}
static const test_case_t* encryption_test_cases()
{
	return ENCRYPTION_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* ENDIAN_TEST_DESCRIPTION;
extern const size_t ENDIAN_TEST_COUNT;
extern const test_case_t ENDIAN_TEST_CASES[];

static size_t endian_test_case_count()
{
	return ENDIAN_TEST_COUNT;
}

static const char* endian_test_description()
{
	return ENDIAN_TEST_DESCRIPTION;
}
static const test_case_t* endian_test_cases()
{
	return ENDIAN_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* FILESYSTEM_TEST_DESCRIPTION;
extern const size_t FILESYSTEM_TEST_COUNT;
extern const test_case_t FILESYSTEM_TEST_CASES[];

static size_t filesystem_test_case_count()
{
	return FILESYSTEM_TEST_COUNT;
}

static const char* filesystem_test_description()
{
	return FILESYSTEM_TEST_DESCRIPTION;
}
static const test_case_t* filesystem_test_cases()
{
	return FILESYSTEM_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* FLOATING_POINT_TEST_DESCRIPTION;
extern const size_t FLOATING_POINT_TEST_COUNT;
extern const test_case_t FLOATING_POINT_TEST_CASES[];

static size_t floating_point_test_case_count()
{
	return FLOATING_POINT_TEST_COUNT;
}

static const char* floating_point_test_description()
{
	return FLOATING_POINT_TEST_DESCRIPTION;
}
static const test_case_t* floating_point_test_cases()
{
	return FLOATING_POINT_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* MEMORY_TEST_DESCRIPTION;
extern const size_t MEMORY_TEST_COUNT;
extern const test_case_t MEMORY_TEST_CASES[];

static size_t memory_test_case_count()
{
	return MEMORY_TEST_COUNT;
}

static const char* memory_test_description()
{
	return MEMORY_TEST_DESCRIPTION;
}
static const test_case_t* memory_test_cases()
{
	return MEMORY_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* REFOBJ_TEST_DESCRIPTION;
extern const size_t REFOBJ_TEST_COUNT;
extern const test_case_t REFOBJ_TEST_CASES[];

static size_t refobj_test_case_count()
{
	return REFOBJ_TEST_COUNT;
}

static const char* refobj_test_description()
{
	return REFOBJ_TEST_DESCRIPTION;
}
static const test_case_t* refobj_test_cases()
{
	return REFOBJ_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* STRING_TEST_DESCRIPTION;
extern const size_t STRING_TEST_COUNT;
extern const test_case_t STRING_TEST_CASES[];

static size_t string_test_case_count()
{
	return STRING_TEST_COUNT;
}

static const char* string_test_description()
{
	return STRING_TEST_DESCRIPTION;
}
static const test_case_t* string_test_cases()
{
	return STRING_TEST_CASES;
}
// ------------------------------------------------------------------
extern const char* TIME_TEST_DESCRIPTION;
extern const size_t TIME_TEST_COUNT;
extern const test_case_t TIME_TEST_CASES[];

static size_t time_test_case_count()
{
	return TIME_TEST_COUNT;
}

static const char* time_test_description()
{
	return TIME_TEST_DESCRIPTION;
}
static const test_case_t* time_test_cases()
{
	return TIME_TEST_CASES;
}


const test_suite_t suites[] = {
	{ checksums_test_description, checksums_test_case_count, checksums_test_cases },
	{ cmdopt_test_description, cmdopt_test_case_count, cmdopt_test_cases },
	{ encoding_test_description, encoding_test_case_count, encoding_test_cases },
	{ encryption_test_description, encryption_test_case_count, encryption_test_cases },
	{ endian_test_description, endian_test_case_count, endian_test_cases },
	{ filesystem_test_description, filesystem_test_case_count, filesystem_test_cases },
	{ floating_point_test_description, floating_point_test_case_count, floating_point_test_cases },
	{ memory_test_description, memory_test_case_count, memory_test_cases },
	{ refobj_test_description, refobj_test_case_count, refobj_test_cases },
	{ string_test_description, string_test_case_count, string_test_cases },
	{ time_test_description, time_test_case_count, time_test_cases },
};
const size_t suites_count = sizeof(suites) / sizeof(suites[0]);

int main(int argc, char* argv[])
{
	size_t fail_count = 0;
	test_suites( suites, suites_count, NULL, &fail_count );
	return fail_count;
}
