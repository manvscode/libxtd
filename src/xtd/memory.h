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
#ifndef _XTD_MEMORY_H_
#define _XTD_MEMORY_H_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
# include <stdint.h>
#else
# error "Need a C99 compiler."
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte_t;

typedef enum size_unit {
	unit_bytes = 0,

	unit_kilobytes,
	unit_megabytes,
	unit_gigabytes,
	unit_terabytes,
	unit_petabytes,
	unit_exabytes,

	unit_kibibytes,
	unit_mebibytes,
	unit_gibibytes,
	unit_tebibytes,
	unit_exibytes
} size_unit_t;

const char*  size_in_unit           ( size_t size, size_unit_t unit, int precision );
const char*  size_in_best_unit      ( size_t size, bool use_base_two, int precision );
const char*  byte_to_binary         ( uint8_t x );
void         buffer_scramble        ( const char* key, void* buffer, size_t size, unsigned short pivot );
void         buffer_unscramble      ( const char* key, void* buffer, size_t size, unsigned short pivot );
void         xor_bytes              ( const void* a, size_t a_size, const void* b, size_t b_size, void* result );
void         swap                   ( void* left, void* right, size_t size );
char*        debug_buffer_to_string ( const void* data, size_t size, size_t grouping, bool with_spaces ); /* allocates memory */
unsigned int rotate_bits_left       ( unsigned int value, int shift );
unsigned int rotate_bits_right      ( unsigned int value, int shift );

/*
 * Macros
 */
#define Ob(x)                           ((unsigned)Ob_(0 ## x ## uL))
#define Ob_(x)                          (x & 1 | x >> 2 & 2 | x >> 4 & 4 | x >> 6 & 8 | x >> 8 & 16 | x >> 10 & 32 | x >> 12 & 64 | x >> 14 & 128)
#define bit_is_disabled( flag, flags )  (!bit_is_set(flag, flags))
#define bit_is_enabled( flag, flags )   (bit_is_set(flag, flags))
#define bit_is_set( flag, flags )       (((flags) & (flag)) != 0)
#define bit_toggle( flag, flags )       ((flags) ^= (flag))
#define bit_set( flag, flags )          ((flags) |= (flag))
#define bit_unset( flag, flags )        ((flags) &= ~(flag))

#ifdef __cplusplus
} /* extern "C" */
namespace utility {
	using ::byte_t;
	using ::size_unit_t;
	using ::size_in_unit;
	using ::size_in_best_unit;
	using ::byte_to_binary;
	using ::buffer_scramble;
	using ::buffer_unscramble;
	using ::xor_bytes;
	using ::swap;
	using ::debug_buffer_to_string;
	using ::rotate_bits_left;
	using::rotate_bits_right;
} /* namespace */
#endif
#endif /* _XTD_MEMORY_H_ */
