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
#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdbool.h>
#include <stdint.h>
#ifdef __restrict
#undef __restrict
#define __restrict restrict
#endif
#ifdef __inline
#undef __inline
#define __inline inline
#endif
#else
#define bool int
#define true 1
#define false 0
#ifdef __restrict
#undef __restrict
#define __restrict
#endif
#ifdef __inline
#undef __inline
#define __inline
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif

/*
 * File IO
 */
bool        file_exists        ( const char* path );
bool        file_is_writeable  ( const char* path );
bool        file_is_readable   ( const char* path );
bool        file_is_executable ( const char* path );
bool        file_copy          ( const char* __restrict src_path, const char* __restrict dst_path );
bool        file_delete        ( const char* path );
long long   file_size          ( const char* path );
long        file_age           ( const char* path ); /* Returns -1 on error */
const char* file_basename      ( const char* filename );
const char* file_extension     ( const char* filename );
char*       file_load_contents ( const char* path, size_t* size );
bool        is_file            ( const char* path );
bool        is_dir             ( const char* path );

typedef enum size_units {
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
} size_units_t;

const char* size_in_units    ( size_t size, size_units_t unit, int precision );
const char* appropriate_size ( size_t size, bool use_base_two, int precision );

/*
 * Compression
 */
bool huffman_encode( const void* __restrict original, size_t size, void** __restrict compressed, size_t* compressed_size );
bool huffman_decode( const void* __restrict compressed, size_t compressed_size, void** __restrict original, size_t* size );

/*
 * Checksums
 */
uint32_t java_hash         ( const uint8_t* data, size_t len );
uint32_t xor8              ( const uint8_t* data, size_t len );
uint32_t adler32           ( const uint8_t* data, size_t len );
uint16_t fletcher16_simple ( uint8_t* data, size_t len );
void     fletcher16        ( uint8_t* checkA, uint8_t* checkB, uint8_t* data, size_t len ); /* faster */
uint32_t fletcher32        ( uint16_t* data, size_t len );

/*
 * Strings
 */
size_t string_left_trim  ( char* s, const char* delimeters );
size_t string_right_trim ( char* s, const char* delimeters );
size_t string_trim       ( char* s, const char* delimeters );
char*  string_to_lower   ( char* s );
char*  string_to_upper   ( char* s );

/*
 * Finite State Machine
 */
typedef short fsm_event_t;
typedef fsm_event_t (*fsm_state_fxn)( void* data );

typedef struct fsm_transition {
    fsm_state_fxn src_state;
    fsm_event_t event;
    fsm_state_fxn dst_state;
} fsm_transition_t;

struct fsm;
typedef struct fsm fsm_t;

fsm_t* fsm_create        ( size_t max_transitions, const fsm_transition_t* transitions, fsm_state_fxn start, fsm_state_fxn end );
void   fsm_destroy       ( fsm_t** fsm );
void   fsm_run           ( fsm_t* fsm, void* data );
bool   fsm_iterative_run ( fsm_t* fsm, void* data );

/*
 * Observers
 */
typedef void (*obs_notify_fxn)( void* observer, void* user_data );

struct obs_subject;
typedef struct obs_subject obs_subject_t;

obs_subject_t* obs_subject_create   ( size_t size, size_t grow_amount );
void           obs_subject_destroy  ( obs_subject_t** p_subject );
bool           obs_subject_register ( obs_subject_t* p_subject, void* observer, obs_notify_fxn notify );
void           obs_subject_notify   ( const obs_subject_t* p_subject, void* user_data );

/*
 * Misscellaneous
 */
typedef enum random_string_type {
	RAND_STRING_ALPHA_NUMERIC = 0,
	RAND_STRING_ALPHA,
	RAND_STRING_HEX,
	RAND_STRING_NUMERIC,
	RAND_STRING_NO_ZERO,
	RAND_STRING_DISTINCT,
} random_string_type_t;

void        print_divider      ( FILE* fd, const char* title );
const char* byte_to_binary     ( uint8_t x );
void        crash              ( void );
void        scramble_string    ( const char* __restrict key, char* __restrict string, size_t len, unsigned short pivot );
void        unscramble_string  ( const char* __restrict key, char* __restrict string, size_t len, unsigned short pivot );
void        random_string      ( random_string_type_t type, char* string, size_t length );
const char* ordinal_string     ( long number );
void        xor_bytes          ( const void* __restrict a, size_t a_size, const void* __restrict b, size_t b_size, void* __restrict result );
void        swap               ( void* __restrict left, void* __restrict right, size_t size );
const char* friendly_size      ( size_t size );
bool        is_big_endian      ( void );
void        hton               ( void* mem, size_t size );
void        ntoh               ( void* mem, size_t size );

/*
 *  Time
 */
double   time_seconds      ( void );
double   time_milliseconds ( void );
uint64_t time_secs         ( void );
uint64_t time_msecs        ( void );

/*
 *  Encryption
 */
void caesar_cypher_encryption ( void* text, size_t size, size_t n );
void caesar_cypher_decryption ( void* text, size_t size, size_t n );

#ifdef __cplusplus
} /* extern "C" */
namespace utility {
	using ::file_exists;
	using ::file_is_writeable;
	using ::file_is_readable;
	using ::file_is_executable;
	using ::file_copy;
	using ::file_delete;
	using ::file_size;
	using ::file_age;
	using ::file_load_contents;
	using ::is_file;
	using ::is_dir;
	using ::size_units_t;
	using ::size_in_units;
	using ::appropriate_size;
	using ::fsm_event_t;
	using ::fsm_state_fxn;
	using ::fsm_transition_t;
	using ::fsm_t;
	using ::fsm_create;
	using ::fsm_destroy;
	using ::fsm_run;
	using ::huffman_encode;
	using ::huffman_decode;
	using ::java_hash;
	using ::xor8;
	using ::adler32;
	using ::fletcher16_simple;
	using ::fletcher16;
	using ::fletcher32;
	using ::random_string_type_t;
	using ::print_divider;
	using ::byte_to_binary;
	using ::crash;
	using ::scramble_string;
	using ::unscramble_string;
	using ::random_string;
	using ::ordinal_string;
	using ::xor_bytes;
	using ::swap;
	using ::friendly_size;
	using ::is_big_endian;
	using ::hton;
	using ::ntoh;
	using ::caesar_cypher_encryption;
	using ::caesar_cypher_decryption;
} /* namespace */
#endif
#endif /* _UTILITY_H_ */
