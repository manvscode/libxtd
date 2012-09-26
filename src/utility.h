/*
 * Copyright (C) 2010 by Joseph A. Marrero and Shrewd LLC. http://www.manvscode.com/
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
#ifndef _UTILITY_H_
#define _UTILITY_H_
#ifdef __cplusplus
extern "C" {
#endif 

#include <stdlib.h>


typedef enum random_string_type {
	RAND_STRING_ALPHA_NUMERIC = 0,
	RAND_STRING_ALPHA,
	RAND_STRING_HEX,
	RAND_STRING_NUMERIC,
	RAND_STRING_NO_ZERO,
	RAND_STRING_DISTINCT,
} random_string_type_t;

void        crash              ( void );
void        scramble_string    ( const char* key, char* string, size_t len, unsigned short pivot );
void        unscramble_string  ( const char* key, char* string, size_t len, unsigned short pivot );
void        random_string      ( random_string_type_t type, char* string, size_t length );
const char* ordinal_string     ( long number );
void        xor_bytes          ( const void* a, size_t a_size, const void* b, size_t b_size, void* result );
void        swap               ( void* left, void *right, size_t size );

/*
 * File IO
 */
int         file_exists        ( const char *path );
int         file_is_writeable  ( const char *path );
int         file_is_readable   ( const char *path );
int         file_is_executable ( const char *path );
int         file_copy          ( const char *src_path, const char *dst_path );
int         file_delete        ( const char *path );
long        file_size          ( const char *path );
int         file_age           ( const char *path ); // Returns -1 on error 
int         is_file            ( const char *path );
int         is_dir             ( const char *path );

#ifdef __cplusplus
}
#endif 
#endif /* _UTILITY_H_ */
