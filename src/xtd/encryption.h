/*
 * Copyright (C) 2010-2025 by Joseph A. Marrero. https://joemarrero.com/
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
#ifndef _ENCRYPTION_H_
#define _ENCRYPTION_H_
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

/*
 *  AES Encryption (ECB single-block primitive).
 */
void aes256_initialize_key (uint8_t key[32], int seed);
void aes256_encrypt_block  (const uint8_t key[32], const uint8_t in[16], uint8_t out[16]);
void aes256_decrypt_block  (const uint8_t key[32], const uint8_t in[16], uint8_t out[16]);

/*
 * AES Encryption for buffers.
 */
void* aes256_encrypt_buffer (const uint8_t key[32], const void* buffer, size_t size, size_t* output_size);
void* aes256_decrypt_buffer (const uint8_t key[32], const void* buffer, size_t size);

/*
 * Insecure Caesar Cypher; for scrambling text naively.
 */
void caesar_cypher_encrypt_buffer (void* buffer, size_t size, int n);
void caesar_cypher_decrypt_buffer (void* buffer, size_t size, int n);
void caesar_cypher_encrypt_text   (char* text, size_t size, int n);
void caesar_cypher_decrypt_text   (char* text, size_t size, int n);


#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
    using ::aes256_encrypt_block;
    using ::aes256_decrypt_block;
    using ::caesar_cypher_encrypt_buffer;
    using ::caesar_cypher_decrypt_buffer;
    using ::caesar_cypher_encrypt_text;
    using ::caesar_cypher_decrypt_text;
} /* namespace */
#endif
#endif /* _ENCRYPTION_H_ */
