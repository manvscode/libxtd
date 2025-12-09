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
#include "xtd/memory.h"
#include "xtd/test.h"

static bool test_aes_encryption (test_ctx_t* ctx)
{
    const char* text = "This is some text that should be protected and unreadable.";
    size_t len = strlen(text);
    const uint8_t key[32] = {
        0xbf, 0x8d, 0xca, 0x9a, 0x60, 0xa2, 0xea, 0xc2, 0x3e, 0x18, 0xa3, 0xfc, 0x74, 0xd9, 0xd8, 0xd0,
        0x5f, 0x0f, 0xa8, 0x41, 0x5e, 0x61, 0x41, 0x8a, 0x80, 0x9f, 0x28, 0xc5, 0x2e, 0x5d, 0x1a, 0x6b
    };
    size_t encrypted_size = 0;
    void* encrypted = aes256_encrypt_buffer(key, text, len + 1, &encrypted_size);

    test_assert_true(ctx, encrypted_size % 16 == 0, "Expected encrypted buffer to be aligned to 16 bytes.");
    test_assert_true(ctx, encrypted_size == 64, "Expected encrypted buffer to be 64 bytes.");
    const uint8_t expected_encrypted[] = {
        0x73, 0x18, 0xe6, 0x13, 0xb6, 0x32, 0x2d, 0x92, 0x9c, 0xf7, 0x1d, 0x46, 0x6d, 0xc8, 0x37, 0xe7,
        0x7a, 0xad, 0xb9, 0x99, 0xc8, 0x6f, 0xbb, 0x37, 0xbc, 0x7f, 0x54, 0x6e, 0x51, 0x02, 0x7b, 0xb4,
        0x77, 0xe6, 0xb9, 0xbb, 0xdc, 0x77, 0x5b, 0xc5, 0x5e, 0x71, 0xc0, 0x7c, 0xd8, 0x1f, 0xab, 0xe3,
        0xb1, 0x28, 0x9e, 0x40, 0x75, 0xac, 0x74, 0x77, 0x64, 0xe5, 0xcb, 0x67, 0x48, 0xec, 0xd0, 0xc7
    };
    test_assert_true(ctx, memcmp(encrypted, expected_encrypted, encrypted_size) == 0, "Expected buffers to be the same.");

    return true;
}

static bool test_aes_decryption (test_ctx_t* ctx)
{
    const uint8_t key[32] = {
        0xbf, 0x8d, 0xca, 0x9a, 0x60, 0xa2, 0xea, 0xc2, 0x3e, 0x18, 0xa3, 0xfc, 0x74, 0xd9, 0xd8, 0xd0,
        0x5f, 0x0f, 0xa8, 0x41, 0x5e, 0x61, 0x41, 0x8a, 0x80, 0x9f, 0x28, 0xc5, 0x2e, 0x5d, 0x1a, 0x6b
    };
    const uint8_t encrypted[] = {
        0x73, 0x18, 0xe6, 0x13, 0xb6, 0x32, 0x2d, 0x92, 0x9c, 0xf7, 0x1d, 0x46, 0x6d, 0xc8, 0x37, 0xe7,
        0x7a, 0xad, 0xb9, 0x99, 0xc8, 0x6f, 0xbb, 0x37, 0xbc, 0x7f, 0x54, 0x6e, 0x51, 0x02, 0x7b, 0xb4,
        0x77, 0xe6, 0xb9, 0xbb, 0xdc, 0x77, 0x5b, 0xc5, 0x5e, 0x71, 0xc0, 0x7c, 0xd8, 0x1f, 0xab, 0xe3,
        0xb1, 0x28, 0x9e, 0x40, 0x75, 0xac, 0x74, 0x77, 0x64, 0xe5, 0xcb, 0x67, 0x48, 0xec, 0xd0, 0xc7
    };
    test_assert_true(ctx, sizeof(encrypted) % 16 == 0, "Expected encrypted buffer to be aligned to 16 bytes.");

    char* decrypted = (char*) aes256_decrypt_buffer (key, encrypted, sizeof(encrypted));
    const char* expected_text = "This is some text that should be protected and unreadable.";
    test_assert_true(ctx, strcmp(decrypted, expected_text) == 0, "Expected source text to be decrypted.");

    return true;
}

const char* ENCRYPTION_TEST_DESCRIPTION = "Testing functions in <xtd/encryption.h>";
const test_case_t ENCRYPTION_TEST_CASES[] = {
    { "Test aes256_encrypt_buffer()", test_aes_encryption },
    { "Test aes256_decrypt_buffer()", test_aes_decryption },
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
