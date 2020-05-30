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
#ifndef _XTD_STRING_H_
#define _XTD_STRING_H_
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum random_string_type {
	RAND_STRING_ALPHA_NUMERIC = 0,
	RAND_STRING_ALPHA,
	RAND_STRING_HEX,
	RAND_STRING_NUMERIC,
	RAND_STRING_NO_ZERO,
	RAND_STRING_DISTINCT,
} string_random_type_t;

/*
 * ASCII and UTF-8 Strings
 */
char*       string_ndup        ( const char* s, size_t len ); /* allocates memory */
char*       string_dup         ( const char* s ); /* allocates memory */
size_t      string_left_trim   ( char* s, const char* delimeters );
size_t      string_right_trim  ( char* s, const char* delimeters );
size_t      string_trim        ( char* s, const char* delimeters );
char*       string_to_lower    ( char* s );
char*       string_to_upper    ( char* s );
void        string_random      ( string_random_type_t type, char* string, size_t length );
const char* string_ordinal     ( long number );
char*       string_replace     ( const char* orig, const char* rep, const char* with ); /* result must be freed */
char*       string_substring   ( const char* str, size_t start, size_t end ); /* result must be freed */
char*       string_tokenize_r  ( char* str, const char* delims, char** saveptr );
char*       string_tokenize    ( char* str, const char* delims );
size_t      string_hash        ( const char* s );
size_t      string_nhash       ( const char* s, size_t len );

/*
 * Multi-byte Strings (UTF-8)
 */
size_t mb_strlen       ( const char* utf8 );
size_t mb_size_at_char ( const char* utf8, int character );

/*
 * Wide Strings
 */
wchar_t* wstring_ndup       ( const wchar_t* s, size_t len ); /* allocates memory */
wchar_t* wstring_dup        ( const wchar_t* s ); /* allocates memory */
size_t   wstring_left_trim  ( wchar_t* s, const wchar_t* delimeters );
size_t   wstring_right_trim ( wchar_t* s, const wchar_t* delimeters );
size_t   wstring_trim       ( wchar_t* s, const wchar_t* delimeters );
wchar_t* wstring_to_lower   ( wchar_t* s );
wchar_t* wstring_to_upper   ( wchar_t* s );
wchar_t* wstring_replace    ( const wchar_t* orig, const wchar_t* rep, const wchar_t* with );
wchar_t* wstring_substring  ( const wchar_t* str, size_t start, size_t end );

#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
	using ::string_random_type_t;
	using ::string_ndup;
	using ::string_dup;
	using ::string_left_trim;
	using ::string_right_trim;
	using ::string_trim;
	using ::string_to_lower;
	using ::string_to_upper;
	using ::string_random;
	using ::string_ordinal;
	using ::string_replace;
	using ::string_substring;
	using ::string_tokenize_r;
	using ::string_tokenize;
	using ::string_hash;
	using ::string_nhash;
	using ::mb_strlen;
	using ::mb_size_at_char;
	using ::wstring_ndup;
	using ::wstring_dup;
	using ::wstring_left_trim;
	using ::wstring_right_trim;
	using ::wstring_trim;
	using ::wstring_to_lower;
	using ::wstring_to_upper;
	using ::wstring_replace;
	using ::wstring_substring;
} /* namespace */
#endif
#endif /* _XTD_STRING_H_ */
