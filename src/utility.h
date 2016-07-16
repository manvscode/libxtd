/*
 * Copyright (C) 2010-2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
#include <stdbool.h>
#include <stdint.h>
#else
#error "Need a C99 compiler."
#endif
#define PATH_REENTRANT  1

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Reference Counting
 */
void* refobj_alloc   ( size_t size, void (*destroy) ( void* ptr ) );
void  refobj_retain  ( void* obj );
void  refobj_release ( void* obj );

/*
 * File IO
 */
typedef void (*file_enumerate_fxn_t) ( const char* filename, void* args );
typedef enum directory_enumerate_mode {
	ENUMERATE_FILES,
	ENUMERATE_DIRECTORIES,
	ENUMERATE_ALL
} directory_enumerate_mode_t;

bool        file_exists              ( const char* path );
bool        file_is_writeable        ( const char* path );
bool        file_is_readable         ( const char* path );
bool        file_is_executable       ( const char* path );
bool        file_copy                ( const char* src_path, const char* dst_path );
bool        file_delete              ( const char* path );
int64_t     file_size                ( const char* path );
const char* file_size_string         ( const char* path, bool use_base_two, int precision );
int64_t     file_age                 ( const char* path ); /* returns -1 on error */
const char* file_basename            ( const char* path );
const char* file_extension           ( const char* filename );
char*       file_load_contents       ( const char* path, size_t* size ); /* allocates memory */
bool        is_file                  ( const char* path );
bool        is_directory             ( const char* path );
bool        directory_exists         ( const char* path );
bool        directory_create         ( const char* path );
char*       directory_path           ( const char* path ); /* allocates memory */
void        directory_enumerate      ( const char* path, bool recursive, directory_enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args );
int         readline                 ( char* buffer, size_t size, FILE* stream );

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

const char* size_in_unit      ( size_t size, size_unit_t unit, int precision );
const char* size_in_best_unit ( size_t size, bool use_base_two, int precision );

/*
 * Checksums and Hashes
 */
uint32_t java_hash         ( const uint8_t* data, size_t len );
uint32_t xor8              ( const uint8_t* data, size_t len );
uint32_t adler32           ( const uint8_t* data, size_t len );
uint16_t fletcher16_simple ( uint8_t* data, size_t len );
void     fletcher16        ( uint8_t* checkA, uint8_t* checkB, uint8_t* data, size_t len ); /* faster */
uint32_t fletcher32        ( uint16_t* data, size_t len );

/*
 * Compression and encodings.
 */
bool  huffman_encode ( const void* original, size_t original_size, void** compressed, size_t* compressed_size );
bool  huffman_decode ( const void* compressed, size_t compressed_size, void** original, size_t* original_size );
char* base64_encode  ( const void* in, size_t in_size, size_t* out_len );
void* base64_decode  ( const char* in, size_t in_len, size_t* out_size );

/*
 * Strings
 */
typedef enum random_string_type {
	RAND_STRING_ALPHA_NUMERIC = 0,
	RAND_STRING_ALPHA,
	RAND_STRING_HEX,
	RAND_STRING_NUMERIC,
	RAND_STRING_NO_ZERO,
	RAND_STRING_DISTINCT,
} string_random_type_t;

size_t      string_left_trim  ( char* s, const char* delimeters );
size_t      string_right_trim ( char* s, const char* delimeters );
size_t      string_trim       ( char* s, const char* delimeters );
char*       string_to_lower   ( char* s );
char*       string_to_upper   ( char* s );
void        string_random     ( string_random_type_t type, char* string, size_t length );
const char* string_ordinal    ( long number );
char*       string_replace    ( const char* orig, const char* rep, const char* with ); /* result must be freed */
char*       string_substring  ( const char* str, size_t start, size_t end );

/*
 * Console
 */
#define CONSOLE_COLOR8_BLACK   30
#define CONSOLE_COLOR8_RED     31
#define CONSOLE_COLOR8_GREEN   32
#define CONSOLE_COLOR8_YELLOW  33
#define CONSOLE_COLOR8_BLUE    34
#define CONSOLE_COLOR8_MAGENTA 35
#define CONSOLE_COLOR8_CYAN    36
#define CONSOLE_COLOR8_WHITE   37

#define CONSOLE_COLOR256_BLACK           0x00
#define CONSOLE_COLOR256_RED             0x01
#define CONSOLE_COLOR256_GREEN           0x02
#define CONSOLE_COLOR256_YELLOW          0x03
#define CONSOLE_COLOR256_BLUE            0x04
#define CONSOLE_COLOR256_MAGENTA         0x05
#define CONSOLE_COLOR256_CYAN            0x06
#define CONSOLE_COLOR256_WHITE           0x07
#define CONSOLE_COLOR256_BRIGHT_BLACK    0x08
#define CONSOLE_COLOR256_BRIGHT_RED      0x09
#define CONSOLE_COLOR256_BRIGHT_GREEN    0x0a
#define CONSOLE_COLOR256_BRIGHT_YELLOW   0x0b
#define CONSOLE_COLOR256_BRIGHT_BLUE     0x0c
#define CONSOLE_COLOR256_BRIGHT_MAGENTA  0x0d
#define CONSOLE_COLOR256_BRIGHT_CYAN     0x0e
#define CONSOLE_COLOR256_BRIGHT_WHITE    0x0f
#if 0
#define CONSOLE_COLOR256_XXX   0x10
#define CONSOLE_COLOR256_XXX   0x11
#define CONSOLE_COLOR256_XXX   0x12
#define CONSOLE_COLOR256_XXX   0x13
#define CONSOLE_COLOR256_XXX   0x14
#define CONSOLE_COLOR256_XXX   0x15
#define CONSOLE_COLOR256_XXX   0x16
#define CONSOLE_COLOR256_XXX   0x17
#define CONSOLE_COLOR256_XXX   0x18
#define CONSOLE_COLOR256_XXX   0x19
#define CONSOLE_COLOR256_XXX   0x1a
#define CONSOLE_COLOR256_XXX   0x1b
#define CONSOLE_COLOR256_XXX   0x1c
#define CONSOLE_COLOR256_XXX   0x1d
#define CONSOLE_COLOR256_XXX   0x1e
#define CONSOLE_COLOR256_XXX   0x1f
#define CONSOLE_COLOR256_XXX   0x20
#define CONSOLE_COLOR256_XXX   0x21
#define CONSOLE_COLOR256_XXX   0x22
#define CONSOLE_COLOR256_XXX   0x23
#define CONSOLE_COLOR256_XXX   0x24
#define CONSOLE_COLOR256_XXX   0x25
#define CONSOLE_COLOR256_XXX   0x26
#define CONSOLE_COLOR256_XXX   0x27
#define CONSOLE_COLOR256_XXX   0x28
#define CONSOLE_COLOR256_XXX   0x29
#define CONSOLE_COLOR256_XXX   0x2a
#define CONSOLE_COLOR256_XXX   0x2b
#define CONSOLE_COLOR256_XXX   0x2c
#define CONSOLE_COLOR256_XXX   0x2d
#define CONSOLE_COLOR256_XXX   0x2e
#define CONSOLE_COLOR256_XXX   0x2f
#define CONSOLE_COLOR256_XXX   0x30
#define CONSOLE_COLOR256_XXX   0x31
#define CONSOLE_COLOR256_XXX   0x32
#define CONSOLE_COLOR256_XXX   0x33
#define CONSOLE_COLOR256_XXX   0x34
#define CONSOLE_COLOR256_XXX   0x35
#define CONSOLE_COLOR256_XXX   0x36
#define CONSOLE_COLOR256_XXX   0x37
#define CONSOLE_COLOR256_XXX   0x38
#define CONSOLE_COLOR256_XXX   0x39
#define CONSOLE_COLOR256_XXX   0x3a
#define CONSOLE_COLOR256_XXX   0x3b
#define CONSOLE_COLOR256_XXX   0x3c
#define CONSOLE_COLOR256_XXX   0x3d
#define CONSOLE_COLOR256_XXX   0x3e
#define CONSOLE_COLOR256_XXX   0x3f
#define CONSOLE_COLOR256_XXX   0x40
#define CONSOLE_COLOR256_XXX   0x41
#define CONSOLE_COLOR256_XXX   0x42
#define CONSOLE_COLOR256_XXX   0x43
#define CONSOLE_COLOR256_XXX   0x44
#define CONSOLE_COLOR256_XXX   0x45
#define CONSOLE_COLOR256_XXX   0x46
#define CONSOLE_COLOR256_XXX   0x47
#define CONSOLE_COLOR256_XXX   0x48
#define CONSOLE_COLOR256_XXX   0x49
#define CONSOLE_COLOR256_XXX   0x4a
#define CONSOLE_COLOR256_XXX   0x4b
#define CONSOLE_COLOR256_XXX   0x4c
#define CONSOLE_COLOR256_XXX   0x4d
#define CONSOLE_COLOR256_XXX   0x4e
#define CONSOLE_COLOR256_XXX   0x4f
#define CONSOLE_COLOR256_XXX   0x50
#define CONSOLE_COLOR256_XXX   0x51
#define CONSOLE_COLOR256_XXX   0x52
#define CONSOLE_COLOR256_XXX   0x53
#define CONSOLE_COLOR256_XXX   0x54
#define CONSOLE_COLOR256_XXX   0x55
#define CONSOLE_COLOR256_XXX   0x56
#define CONSOLE_COLOR256_XXX   0x57
#define CONSOLE_COLOR256_XXX   0x58
#define CONSOLE_COLOR256_XXX   0x59
#define CONSOLE_COLOR256_XXX   0x5a
#define CONSOLE_COLOR256_XXX   0x5b
#define CONSOLE_COLOR256_XXX   0x5c
#define CONSOLE_COLOR256_XXX   0x5d
#define CONSOLE_COLOR256_XXX   0x5e
#define CONSOLE_COLOR256_XXX   0x5f
#define CONSOLE_COLOR256_XXX   0x60
#define CONSOLE_COLOR256_XXX   0x61
#define CONSOLE_COLOR256_XXX   0x62
#define CONSOLE_COLOR256_XXX   0x63
#define CONSOLE_COLOR256_XXX   0x64
#define CONSOLE_COLOR256_XXX   0x65
#define CONSOLE_COLOR256_XXX   0x66
#define CONSOLE_COLOR256_XXX   0x67
#define CONSOLE_COLOR256_XXX   0x68
#define CONSOLE_COLOR256_XXX   0x69
#define CONSOLE_COLOR256_XXX   0x6a
#define CONSOLE_COLOR256_XXX   0x6b
#define CONSOLE_COLOR256_XXX   0x6c
#define CONSOLE_COLOR256_XXX   0x6d
#define CONSOLE_COLOR256_XXX   0x6e
#define CONSOLE_COLOR256_XXX   0x6f
#define CONSOLE_COLOR256_XXX   0x70
#define CONSOLE_COLOR256_XXX   0x71
#define CONSOLE_COLOR256_XXX   0x72
#define CONSOLE_COLOR256_XXX   0x73
#define CONSOLE_COLOR256_XXX   0x74
#define CONSOLE_COLOR256_XXX   0x75
#define CONSOLE_COLOR256_XXX   0x76
#define CONSOLE_COLOR256_XXX   0x77
#define CONSOLE_COLOR256_XXX   0x78
#define CONSOLE_COLOR256_XXX   0x79
#define CONSOLE_COLOR256_XXX   0x7a
#define CONSOLE_COLOR256_XXX   0x7b
#define CONSOLE_COLOR256_XXX   0x7c
#define CONSOLE_COLOR256_XXX   0x7d
#define CONSOLE_COLOR256_XXX   0x7e
#define CONSOLE_COLOR256_XXX   0x7f
#define CONSOLE_COLOR256_XXX   0x80
#define CONSOLE_COLOR256_XXX   0x81
#define CONSOLE_COLOR256_XXX   0x82
#define CONSOLE_COLOR256_XXX   0x83
#define CONSOLE_COLOR256_XXX   0x84
#define CONSOLE_COLOR256_XXX   0x85
#define CONSOLE_COLOR256_XXX   0x86
#define CONSOLE_COLOR256_XXX   0x87
#define CONSOLE_COLOR256_XXX   0x88
#define CONSOLE_COLOR256_XXX   0x89
#define CONSOLE_COLOR256_XXX   0x8a
#define CONSOLE_COLOR256_XXX   0x8b
#define CONSOLE_COLOR256_XXX   0x8c
#define CONSOLE_COLOR256_XXX   0x8d
#define CONSOLE_COLOR256_XXX   0x8e
#define CONSOLE_COLOR256_XXX   0x8f
#define CONSOLE_COLOR256_XXX   0x90
#define CONSOLE_COLOR256_XXX   0x91
#define CONSOLE_COLOR256_XXX   0x92
#define CONSOLE_COLOR256_XXX   0x93
#define CONSOLE_COLOR256_XXX   0x94
#define CONSOLE_COLOR256_XXX   0x95
#define CONSOLE_COLOR256_XXX   0x96
#define CONSOLE_COLOR256_XXX   0x97
#define CONSOLE_COLOR256_XXX   0x98
#define CONSOLE_COLOR256_XXX   0x99
#define CONSOLE_COLOR256_XXX   0x9a
#define CONSOLE_COLOR256_XXX   0x9b
#define CONSOLE_COLOR256_XXX   0x9c
#define CONSOLE_COLOR256_XXX   0x9d
#define CONSOLE_COLOR256_XXX   0x9e
#define CONSOLE_COLOR256_XXX   0x9f
#define CONSOLE_COLOR256_XXX   0xa0
#define CONSOLE_COLOR256_XXX   0xa1
#define CONSOLE_COLOR256_XXX   0xa2
#define CONSOLE_COLOR256_XXX   0xa3
#define CONSOLE_COLOR256_XXX   0xa4
#define CONSOLE_COLOR256_XXX   0xa5
#define CONSOLE_COLOR256_XXX   0xa6
#define CONSOLE_COLOR256_XXX   0xa7
#define CONSOLE_COLOR256_XXX   0xa8
#define CONSOLE_COLOR256_XXX   0xa9
#define CONSOLE_COLOR256_XXX   0xaa
#define CONSOLE_COLOR256_XXX   0xab
#define CONSOLE_COLOR256_XXX   0xac
#define CONSOLE_COLOR256_XXX   0xad
#define CONSOLE_COLOR256_XXX   0xae
#define CONSOLE_COLOR256_XXX   0xaf
#define CONSOLE_COLOR256_XXX   0xb0
#define CONSOLE_COLOR256_XXX   0xb1
#define CONSOLE_COLOR256_XXX   0xb2
#define CONSOLE_COLOR256_XXX   0xb3
#define CONSOLE_COLOR256_XXX   0xb4
#define CONSOLE_COLOR256_XXX   0xb5
#define CONSOLE_COLOR256_XXX   0xb6
#define CONSOLE_COLOR256_XXX   0xb7
#define CONSOLE_COLOR256_XXX   0xb8
#define CONSOLE_COLOR256_XXX   0xb9
#define CONSOLE_COLOR256_XXX   0xba
#define CONSOLE_COLOR256_XXX   0xbb
#define CONSOLE_COLOR256_XXX   0xbc
#define CONSOLE_COLOR256_XXX   0xbd
#define CONSOLE_COLOR256_XXX   0xbe
#define CONSOLE_COLOR256_XXX   0xbf
#define CONSOLE_COLOR256_XXX   0xc0
#define CONSOLE_COLOR256_XXX   0xc1
#define CONSOLE_COLOR256_XXX   0xc2
#define CONSOLE_COLOR256_XXX   0xc3
#define CONSOLE_COLOR256_XXX   0xc4
#define CONSOLE_COLOR256_XXX   0xc5
#define CONSOLE_COLOR256_XXX   0xc6
#define CONSOLE_COLOR256_XXX   0xc7
#define CONSOLE_COLOR256_XXX   0xc8
#define CONSOLE_COLOR256_XXX   0xc9
#define CONSOLE_COLOR256_XXX   0xca
#define CONSOLE_COLOR256_XXX   0xcb
#define CONSOLE_COLOR256_XXX   0xcc
#define CONSOLE_COLOR256_XXX   0xcd
#define CONSOLE_COLOR256_XXX   0xce
#define CONSOLE_COLOR256_XXX   0xcf
#define CONSOLE_COLOR256_XXX   0xd0
#define CONSOLE_COLOR256_XXX   0xd1
#define CONSOLE_COLOR256_XXX   0xd2
#define CONSOLE_COLOR256_XXX   0xd3
#define CONSOLE_COLOR256_XXX   0xd4
#define CONSOLE_COLOR256_XXX   0xd5
#define CONSOLE_COLOR256_XXX   0xd6
#define CONSOLE_COLOR256_XXX   0xd7
#define CONSOLE_COLOR256_XXX   0xd8
#define CONSOLE_COLOR256_XXX   0xd9
#define CONSOLE_COLOR256_XXX   0xda
#define CONSOLE_COLOR256_XXX   0xdb
#define CONSOLE_COLOR256_XXX   0xdc
#define CONSOLE_COLOR256_XXX   0xdd
#define CONSOLE_COLOR256_XXX   0xde
#define CONSOLE_COLOR256_XXX   0xdf
#define CONSOLE_COLOR256_XXX   0xe0
#define CONSOLE_COLOR256_XXX   0xe1
#define CONSOLE_COLOR256_XXX   0xe2
#define CONSOLE_COLOR256_XXX   0xe3
#define CONSOLE_COLOR256_XXX   0xe4
#define CONSOLE_COLOR256_XXX   0xe5
#define CONSOLE_COLOR256_XXX   0xe6
#define CONSOLE_COLOR256_XXX   0xe7
#endif

#define CONSOLE_COLOR256_GREY_00   0xe8
#define CONSOLE_COLOR256_GREY_01   0xe9
#define CONSOLE_COLOR256_GREY_02   0xea
#define CONSOLE_COLOR256_GREY_03   0xeb
#define CONSOLE_COLOR256_GREY_04   0xec
#define CONSOLE_COLOR256_GREY_05   0xed
#define CONSOLE_COLOR256_GREY_06   0xee
#define CONSOLE_COLOR256_GREY_07   0xef
#define CONSOLE_COLOR256_GREY_08   0xf0
#define CONSOLE_COLOR256_GREY_09   0xf1
#define CONSOLE_COLOR256_GREY_10   0xf2
#define CONSOLE_COLOR256_GREY_11   0xf3
#define CONSOLE_COLOR256_GREY_12   0xf4
#define CONSOLE_COLOR256_GREY_13   0xf5
#define CONSOLE_COLOR256_GREY_14   0xf6
#define CONSOLE_COLOR256_GREY_15   0xf7
#define CONSOLE_COLOR256_GREY_16   0xf8
#define CONSOLE_COLOR256_GREY_17   0xf9
#define CONSOLE_COLOR256_GREY_18   0xfa
#define CONSOLE_COLOR256_GREY_19   0xfb
#define CONSOLE_COLOR256_GREY_20   0xfc
#define CONSOLE_COLOR256_GREY_21   0xfd
#define CONSOLE_COLOR256_GREY_22   0xfe
#define CONSOLE_COLOR256_GREY_23   0xff

typedef void (*console_progress_fxn_t)       ( int* percent, void* data );
typedef bool (*console_handle_command_fxn_t) ( const char* command, void* data );
typedef enum console_progress_indictor_style {
    PROGRESS_INDICATOR_STYLE_BLUE,
    PROGRESS_INDICATOR_STYLE_FADE,
    PROGRESS_INDICATOR_STYLE_INTENSITY,
} console_progress_indictor_style_t;

typedef enum console_text_fader_style {
    TEXT_FADER_TO_WHITE,
    TEXT_FADER_TO_BLACK,
    TEXT_FADER_TO_YELLOW,
    TEXT_FADER_TO_ORANGE,
    TEXT_FADER_TO_GREEN,
    TEXT_FADER_TO_BLUE,
    TEXT_FADER_TO_RED,
    TEXT_FADER_BLUE_BEEP,
} console_text_fader_style_t;

void console_fg_color_8            ( int color );
void console_fg_bright_color_8     ( int color );
void console_fg_color_256          ( int color );
void console_bg_color_256          ( int color );
void console_bold                  ( void );
void console_underline             ( void );
void console_reversed              ( void );
void console_hide_cursor           ( void );
void console_show_cursor           ( void );
void console_reset                 ( void );
void console_save_position         ( void );
void console_restore_position      ( void );
void console_move_up               ( int n );
void console_move_down             ( int n );
void console_move_left             ( int n );
void console_move_right            ( int n );
void console_bar_graph             ( int bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, int percent );
void console_progress_indicator_ex ( const char* task, int progress_bar_width, char bar_symbol, const int* colors, size_t color_count, int bkg_color, console_progress_fxn_t fxn, void* data );
void console_progress_indicator    ( const char* task, console_progress_indictor_style_t style, console_progress_fxn_t fxn, void* data );
void console_next_line             ( int n );
void console_prev_line             ( int n );
void console_set_column            ( int x );
void console_goto                  ( int x, int y );
void console_clear_screen          ( int type );
void console_clear_line            ( int type );
void console_text_fader_ex         ( const char* text, const int* colors, size_t color_count, int millis );
void console_text_fader            ( const char* text, console_text_fader_style_t style );
void console_command_prompt        ( const char* prompt, int prompt_color, console_handle_command_fxn_t on_cmd, void* data );
#define console_clear_screen_to_end()    console_clear_screen( 0 ) // clears from cursor to end of screen
#define console_clear_screen_from_beg()  console_clear_screen( 1 ) // clears from cursor to start of screen
#define console_clear_screen_all()       console_clear_screen( 2 ) // clears whole screen
#define console_clear_line_to_end()      console_clear_line( 0 ) // from cursor to end of line
#define console_clear_line_from_beg()    console_clear_line( 1 ) // from cursor to start of line
#define console_clear_line_all()         console_clear_line( 2 ) // clears whole line
void print_divider                 ( FILE* fd, const char* title );


/*
 * Misscellaneous
 */

const char* byte_to_binary         ( uint8_t x );
void        buffer_scramble        ( const char* key, void* buffer, size_t size, unsigned short pivot );
void        buffer_unscramble      ( const char* key, void* buffer, size_t size, unsigned short pivot );
void        xor_bytes              ( const void* a, size_t a_size, const void* b, size_t b_size, void* result );
void        swap                   ( void* left, void* right, size_t size );
bool        is_big_endian          ( void );
void        hton                   ( void* mem, size_t size );
void        ntoh                   ( void* mem, size_t size );
char*       debug_buffer_to_string ( const void* data, size_t size, size_t grouping, bool with_spaces ); /* allocates memory */

/*
 *  Timer
 */
double   time_seconds      ( void );
double   time_milliseconds ( void );
uint64_t time_secs         ( void );
uint64_t time_msecs        ( void );
void     time_msleep       ( int milliseconds );

/*
 *  Encryption
 */
void caesar_cypher_encrypt_buffer ( void* buffer, size_t size, int n );
void caesar_cypher_decrypt_buffer ( void* buffer, size_t size, int n );
void caesar_cypher_encrypt_text   ( char* text, size_t size, int n );
void caesar_cypher_decrypt_text   ( char* text, size_t size, int n );

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
	using ::file_exists;
	using ::file_is_writeable;
	using ::file_is_readable;
	using ::file_is_executable;
	using ::file_copy;
	using ::file_delete;
	using ::file_size;
	using ::file_size_string;
	using ::file_age;
	using ::file_basename;
	using ::file_load_contents;
	using ::is_file;
	using ::is_directory;
	using ::directory_exists;
	using ::directory_create;
	using ::directory_path;
	using ::directory_enumerate;
	using ::file_enumerate_fxn_t;
	using ::size_unit_t;
	using ::size_in_unit;
	using ::size_in_best_unit;
	using ::java_hash;
	using ::xor8;
	using ::adler32;
	using ::fletcher16_simple;
	using ::fletcher16;
	using ::fletcher32;
	using ::huffman_encode;
	using ::huffman_decode;
	using ::string_random_type_t;
	using ::print_divider;
	using ::byte_to_binary;
	using ::buffer_scramble;
	using ::buffer_unscramble;
	using ::string_random;
	using ::string_ordinal;
	using ::xor_bytes;
	using ::swap;
	using ::is_big_endian;
	using ::hton;
	using ::ntoh;
	using ::debug_buffer_to_string;
	using ::time_seconds;
	using ::time_milliseconds;
	using ::time_secs;
	using ::time_msecs;
	using ::time_msleep;
	using ::caesar_cypher_encrypt_buffer;
	using ::caesar_cypher_decrypt_buffer;
	using ::caesar_cypher_encrypt_text;
	using ::caesar_cypher_decrypt_text;
} /* namespace */
#endif
#endif /* _UTILITY_H_ */
