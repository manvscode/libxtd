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
#include "xtd/encryption.h"
#include "xtd/test.h"


const char* ENCRYPTION_TEST_DESCRIPTION = "Testing functions in <xtd/encryption.h>";
const test_case_t ENCRYPTION_TEST_CASES[] = {
    { "Test caesar_cypher_encrypt_buffer()", test_nil },
    { "Test caesar_cypher_decrypt_buffer()", test_nil },
    { "Test caesar_cypher_encrypt_text()", test_nil },
    { "Test caesar_cypher_decrypt_text()", test_nil },
};
const size_t ENCRYPTION_TEST_COUNT = sizeof(ENCRYPTION_TEST_CASES) / sizeof(ENCRYPTION_TEST_CASES[0]);

#ifdef TEST_ENCRYPTION
int main(int argc, char* argv[])
{
    size_t pass_count = test_features(ENCRYPTION_TEST_DESCRIPTION, ENCRYPTION_TEST_CASES, ENCRYPTION_TEST_COUNT, true);
    return ENCRYPTION_TEST_COUNT - pass_count;
}
#endif
