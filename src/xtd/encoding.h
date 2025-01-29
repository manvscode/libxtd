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
#ifndef _ENCODING_H_
#define _ENCODING_H_
#include <stdlib.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
#else
# error "Need a C99 compiler."
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Compression and encodings.
 */
bool  huffman_encode ( const void* original, size_t original_size, void** compressed, size_t* compressed_size );
bool  huffman_decode ( const void* compressed, size_t compressed_size, void** original, size_t* original_size );
char* base64_encode  ( const void* in, size_t in_size, size_t* out_len );
void* base64_decode  ( const char* in, size_t in_len, size_t* out_len );


#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
	using ::huffman_encode;
	using ::huffman_decode;
	using ::base64_encode;
	using ::base64_decode;
} /* namespace */
#endif
#endif /* _ENCODING_H_ */
