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
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "xtd/string.h"
#include "xtd/test.h"

bool test_string_ndup(test_ctx_t* ctx);
bool test_string_dup(test_ctx_t* ctx);
bool test_string_left_trim(test_ctx_t* ctx);
bool test_string_right_trim(test_ctx_t* ctx);
bool test_string_trim(test_ctx_t* ctx);
bool test_string_to_lower(test_ctx_t* ctx);
bool test_string_to_upper(test_ctx_t* ctx);
bool test_string_random(test_ctx_t* ctx);
bool test_string_ordinal(test_ctx_t* ctx);
bool test_string_replace(test_ctx_t* ctx);
bool test_string_substring(test_ctx_t* ctx);

bool test_string_tokenize_r(test_ctx_t* ctx);
bool test_string_tokenize(test_ctx_t* ctx);
bool test_string_hash(test_ctx_t* ctx);
bool test_string_nhash(test_ctx_t* ctx);


const char* STRING_TEST_DESCRIPTION = "Testing functions in <xtd/string.h>";
const test_case_t STRING_TEST_CASES[] = {
    { "Test string_ndup()", test_string_ndup },
    { "Test string_dup()", test_string_dup },
    { "Test string_left_trim()", test_string_left_trim },
    { "Test string_right_trim()", test_string_right_trim },
    { "Test string_trim()", test_string_trim },
    { "Test string_to_lower()", test_string_to_lower },
    { "Test string_to_upper()", test_string_to_upper },
    { "Test string_random()", test_string_random },
    { "Test string_ordinal()", test_string_ordinal },
    { "Test string_replace()", test_string_replace },
    { "Test string_substring()", test_string_substring },
    { "Test string_tokenize_r()", test_string_tokenize_r },
    { "Test string_tokenize()", test_string_tokenize },
    { "Test string_hash()", test_string_hash },
    { "Test string_nhash()", test_string_nhash },
};
const size_t STRING_TEST_COUNT = sizeof(STRING_TEST_CASES) / sizeof(STRING_TEST_CASES[0]);

bool test_string_ndup(test_ctx_t* ctx)
{
    bool result = true;
    const char* sourceX = "This is a test string.XX";
    size_t len = strlen(sourceX) - 1;
    char* copy = string_ndup(sourceX, len); // allocates memory
    copy[ len ] = '\0';

    if (!test_assert_true(ctx, copy != NULL, "Allocation failed."))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, strlen(copy), len, "Duplicated string must have a length of %zu", len))
    {
        result = false;
        goto done;
    }

done:
    if (copy) free(copy);
    return result;
}

bool test_string_dup(test_ctx_t* ctx)
{
    bool result = true;
    const char* sourceX = "This is a test string.XX";
    size_t len = strlen(sourceX) - 1;
    char* copy = string_dup(sourceX); // allocates memory
    copy[ len ] = '\0';

    if (!test_assert_true(ctx, copy != NULL, "Allocation failed."))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, strlen(copy), len, "Duplicated string must have a length of %zu", len))
    {
        result = false;
        goto done;
    }

done:
    if (copy) free(copy);
    return result;
}

bool test_string_left_trim(test_ctx_t* ctx)
{
    bool result = true;
    char string[] = "\t  \n \r  \t TEXT  ";

    size_t sz = string_left_trim(string, "\t\n\r ");

    if (!test_assert_equals(ctx, string, "TEXT  ", "Expected string should be a \"TEXT  \" but encounted \"%s\"", string))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, sz, 10UL, "Expected 10 chars trimmed but encounted \"%zu\"", sz))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_right_trim(test_ctx_t* ctx)
{
    bool result = true;
    char string[] = "  TEXT\t \r \n\t\t   ";

    size_t sz = string_right_trim(string, "\t\n\r ");

    if (!test_assert_equals(ctx, string, "  TEXT", "Expected string should be a \"  TEXT\" but encounted \"%s\"", string))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, sz, 10UL, "Expected 10 chars trimmed but encounted \"%zu\"", sz))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_trim(test_ctx_t* ctx)
{
    bool result = true;
    char string[] = " \t \n\r  TEXT\t \r \n\t\t   ";

    size_t sz = string_trim(string, "\t\n\r ");

    if (!test_assert_equals(ctx, string, "TEXT", "Expected string should be a \"TEXT\" but encounted \"%s\"", string))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, sz, 17UL, "Expected 17 chars trimmed but encounted \"%zu\"", sz))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_to_lower(test_ctx_t* ctx)
{
    bool result = true;
    char string[] = "TEXT";

    string_to_lower(string);

    if (!test_assert_equals(ctx, string, "text", "Expected string should be a \"text\" but encounted \"%s\"", string))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_to_upper(test_ctx_t* ctx)
{
    bool result = true;
    char string[] = "text";

    string_to_upper(string);

    if (!test_assert_equals(ctx, string, "TEXT", "Expected string should be a \"TEXT\" but encounted \"%s\"", string))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_random(test_ctx_t* ctx)
{
    bool result = true;
    char alpha_numeric[32];
    char alpha_numeric_invalid[] = "!@#$%^&*()<>?:{}\\/~";

    string_random(RAND_STRING_ALPHA_NUMERIC, alpha_numeric, sizeof(alpha_numeric) - 1);
    if (!test_assert_true(ctx, strlen(alpha_numeric) == 31, "Expected alpha-numeric string length to be 31."))
    {
        result = false;
        goto done;
    }

    for (int i = 0; i < sizeof(alpha_numeric_invalid) - 1; i++)
    {
        if (!test_assert_true(ctx, strchr(alpha_numeric, alpha_numeric_invalid[i]) == NULL, "Expected alpha-numeric string not contain any '%c' characters.", alpha_numeric_invalid[i]))
        {
            result = false;
            goto done;
        }
    }

    char hex[128];
    char hex_invalid[] = "!@#$%^&*()<>?:{}\\/~ghijklmnopqrstuvwxyzGHIJKLMNOPQRSTUVWXYZ";

    string_random(RAND_STRING_HEX, hex, sizeof(hex) - 1);
    if (!test_assert_true(ctx, strlen(hex) == (sizeof(hex) - 1), "Expected alpha-numeric string length to be %ld.", sizeof(hex) - 1))
    {
        result = false;
        goto done;
    }

    for (int i = 0; i < sizeof(hex_invalid) - 1; i++)
    {
        if (!test_assert_true(ctx, strchr(hex, hex_invalid[i]) == NULL, "Expected hex string not contain any '%c' characters.", hex_invalid[i]))
        {
            result = false;
            goto done;
        }
    }

done:
    return result;
}

bool test_string_ordinal(test_ctx_t* ctx)
{
    bool result = true;
    const char* ordinal;

    ordinal = string_ordinal(1);
    if (!test_assert_equals(ctx, ordinal, "st", "Expected first to end with \"%s\"", ordinal))
    {
        result = false;
        goto done;
    }

    ordinal = string_ordinal(2);
    if (!test_assert_equals(ctx, ordinal, "nd", "Expected second to end with \"%s\"", ordinal))
    {
        result = false;
        goto done;
    }

    ordinal = string_ordinal(3);
    if (!test_assert_equals(ctx, ordinal, "rd", "Expected third to end with \"%s\"", ordinal))
    {
        result = false;
        goto done;
    }

    ordinal = string_ordinal(4);
    if (!test_assert_equals(ctx, ordinal, "th", "Expected fourth to end with \"%s\"", ordinal))
    {
        result = false;
        goto done;
    }

    ordinal = string_ordinal(19);
    if (!test_assert_equals(ctx, ordinal, "th", "Expected nineteenth to end with \"%s\"", ordinal))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_replace(test_ctx_t* ctx)
{
    bool result = true;

    const char* original = "Hi Joe, where are you going?";
    const char* replace = "Joe";
    const char* with = "Mike";

    char* result_string = string_replace(original, replace, with);

    if (!test_assert_not_null(ctx, result_string, "Expected result string not to be NULL"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, result_string, "Hi Mike, where are you going?", "Expected replaced string to contain \"Mike\""))
    {
        result = false;
        goto done;
    }

done:
    if (result_string) free(result_string);
    return result;
}

bool test_string_substring(test_ctx_t* ctx)
{
    bool result = true;
    const char* str = "Hello, Joe, how are you doing?";

    char* sub = string_substring(str, 7, 10);

    if (!test_assert_not_null(ctx, sub, "Expected substring not to be NULL"))
    {
        result = false;
        goto done;
    }

    if (!test_assert_equals(ctx, sub, "Joe", "Expected substring to be \"Joe\" but it was \"%s\"", sub))
    {
        result = false;
        goto done;
    }


done:
    if (sub) free(sub);
    return result;
}

bool test_string_tokenize_r(test_ctx_t* ctx)
{
    bool result = true;
    const char* delims = ",";
    char string[] = "apple,banana,,  strawberry";
    char* saveptr = NULL;

    const char* field = string_tokenize_r(string, delims, &saveptr);
    if (!test_assert_equals(ctx, field, "apple", "First item should be a \"apple\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize_r(NULL, delims, &saveptr);
    if (!test_assert_equals(ctx, field, "banana", "Second item should be a \"banana\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize_r(NULL, delims, &saveptr);
    if (!test_assert_equals(ctx, field, "", "Third item should be a \"\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize_r(NULL, delims, &saveptr);
    if (!test_assert_equals(ctx, field, "  strawberry", "Fourth item should be a \"  strawberry\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize_r(NULL, delims, &saveptr);
    if (!test_assert_equals(ctx, (void*)field, NULL, "Last item should be NULL."))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_tokenize(test_ctx_t* ctx)
{
    bool result = true;
    const char* delims = ",;";
    char string1[] = "one; two,;\tfour";

    const char* field = string_tokenize(string1, delims);
    if (!test_assert_equals(ctx, field, "one", "First item should be a \"one\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize(NULL, delims);
    if (!test_assert_equals(ctx, field, " two", "Second item should be a \" two\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize(NULL, delims);
    if (!test_assert_equals(ctx, field, "", "Third item should be a \"\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize(NULL, delims);
    if (!test_assert_equals(ctx, field, "\tfour", "Fourth item should be a \"\tfour\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize(NULL, delims);
    if (!test_assert_equals(ctx, (void*)field, NULL, "Last item should be NULL."))
    {
        result = false;
        goto done;
    }

    char string2[] = "dir1;dir2";

    field = string_tokenize(string2, delims);
    if (!test_assert_equals(ctx, field, "dir1", "First item should be a \"dir1\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize(NULL, delims);
    if (!test_assert_equals(ctx, field, "dir2", "Second item should be a \"dir2\" string."))
    {
        result = false;
        goto done;
    }

    field = string_tokenize(NULL, delims);
    if (!test_assert_equals(ctx, (void*)field, NULL, "Last item should be NULL."))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_hash(test_ctx_t* ctx)
{
    bool result = true;
    const char* s = "Hello World";
    size_t hash = string_hash(s);

    if (!test_assert_equals(ctx, hash, 61778821608020612UL, "Expected hash of \"%s\" to be %zu.", s, hash))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

bool test_string_nhash(test_ctx_t* ctx)
{
    bool result = true;
    const char* s = "Hello World";
    size_t hash = string_nhash(s, 5);

    if (!test_assert_equals(ctx, hash, 69609650UL, "Expected hash of \"%s\" to be %zu.", s, hash))
    {
        result = false;
        goto done;
    }

done:
    return result;
}

#ifdef TEST_STRING
int main(int argc, char* argv[])
{
    size_t pass_count = test_features(STRING_TEST_DESCRIPTION, STRING_TEST_CASES, STRING_TEST_COUNT, true);
    return STRING_TEST_COUNT - pass_count;
}
#endif
