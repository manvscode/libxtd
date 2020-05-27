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
#ifndef _XTD_CHECKSUMS_H_
#define _XTD_CHECKSUMS_H_
#include <stdlib.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
# include <stdint.h>
#else
# error "Need a C99 compiler."
#endif
#define PATH_REENTRANT  1

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Checksums
 */
uint32_t java_hash         ( const uint8_t* data, size_t len );
uint32_t xor8              ( const uint8_t* data, size_t len );
uint32_t adler32           ( const uint8_t* data, size_t len );
uint16_t fletcher16_simple ( uint8_t* data, size_t len );
void     fletcher16        ( uint8_t* check_a, uint8_t* check_b, uint8_t* data, size_t len ); /* faster */
uint32_t fletcher32        ( uint16_t* data, size_t len );

#ifdef __cplusplus
} /* extern "C" */
namespace utility {
	using ::java_hash;
	using ::xor8;
	using ::adler32;
	using ::fletcher16_simple;
	using ::fletcher16;
	using ::fletcher32;
} /* namespace */
#endif
#endif /* _XTD_CHECKSUMS_H_ */
