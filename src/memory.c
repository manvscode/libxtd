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
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "xtd/memory.h"

#ifdef _WIN32
#define snprintf  _snprintf
#endif

static uint64_t size_powers[] = {
    1,                   // 10^0, 2^0 byte

    1000,                // 10^3   kilobyte
    1000000,             // 10^6   megabyte
    1000000000,          // 10^9   gigabyte
    1000000000000,       // 10^12  terabyte
    1000000000000000,    // 10^15  petabyte
    1000000000000000000, // 10^18  exabyte

    1024,                // 2^10   kibibyte
    1048576,             // 2^20   mebibyte
    1073741824,          // 2^30   gibibyte
    1099511627776,       // 2^40   tebibyte
    1125899906842624,    // 2^50   pebibyte
    1152921504606846976, // 2^60   exibyte
};

static const char* size_units[] = {
    "B",       // 0
    "KB",      // 1
    "MB",      // 2
    "GB",      // 3
    "TB",      // 4
    "PB",      // 5
    "EB",      // 6
    "KiB",     // 7
    "MiB",     // 8
    "GiB",     // 9
    "TiB",     // 10
    "PiB",     // 11
    "EiB"      // 12
};

const char* size_in_unit(size_t size, size_unit_t unit, int precision)
{
    double unit_size = ((double) size) / size_powers[ unit ];

#if REENTRANT
    size_t len = snprintf(NULL, 0, "%lf %s", unit_size, size_units[ unit ]);

    result = malloc((len + 1) * sizeof(char));
    if (result)
    {
        len = snprintf(result, len + 1, "%.*lf %s", precision, unit_size, size_units[ unit ]);
    }
#else
    static char result[ 128 ];
    snprintf(result, sizeof(result), "%.*lf %s", precision, unit_size, size_units[ unit ]);
#endif

    return result;
}

const char* size_in_best_unit(size_t size, bool use_base_two, int precision)
{
    uint16_t t = use_base_two ? unit_kibibytes - unit_kilobytes : 0;

    if (size < size_powers[ unit_kilobytes + t ])
    {
        return size_in_unit(size, unit_bytes, precision);
    }
    else if (size < size_powers[ unit_megabytes + t])
    {
        return size_in_unit(size, unit_kilobytes + t, precision);
    }
    else if (size < size_powers[ unit_gigabytes + t])
    {
        return size_in_unit(size, unit_megabytes + t, precision);
    }
    else if (size < size_powers[ unit_terabytes + t])
    {
        return size_in_unit(size, unit_gigabytes + t, precision);
    }
    else if (size < size_powers[ unit_petabytes + t])
    {
        return size_in_unit(size, unit_terabytes + t, precision);
    }
    else if (size < size_powers[ unit_exabytes + t])
    {
        return size_in_unit(size, unit_petabytes + t, precision);
    }

    // otherwise display in bytes
    return size_in_unit(size, unit_bytes, 1);
}

const char* byte_to_binary(uint8_t x)
{
    static char b[ CHAR_BIT + 1 ];
    b[0] = '\0';

    for (uint16_t z = SCHAR_MAX + 1; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

void buffer_scramble(const char* key, void* buffer, size_t size, unsigned short pivot)
{
    size_t key_len  = strlen(key);
    unsigned char* bytes = (unsigned char*) buffer;
    int64_t sz = size;

    while (sz >= 0)
    {
        bytes[ sz ] = (bytes[ sz ] + pivot) % 256;
        bytes[ sz ] = (byte_t) (bytes[sz] ^ key[sz % key_len]);
        sz--;
    }
}

void buffer_unscramble(const char* key, void* buffer, size_t size, unsigned short pivot)
{
    size_t key_len  = strlen(key);
    unsigned char* bytes = (unsigned char*) buffer;
    int64_t sz = size;

    while (sz >= 0)
    {
        bytes[ sz ] = (byte_t) (bytes[sz] ^ key[sz % key_len]);
        bytes[ sz ] = (bytes[ sz ] - pivot) % 256;
        sz--;
    }
}

void xor_bytes(const void* a, size_t a_size, const void* b, size_t b_size, void* result)
{
    const byte_t* p_a = a;
    const byte_t* p_b = b;
    byte_t* p_r       = result;
    long i            = b_size;

    while (i >= 0)
    {
        p_r[ i ] = (byte_t) (p_b[i] ^ p_a[i % (a_size + 1)]);
        i--;
    }
}

void swap(void* left, void* right, size_t size)
{
#if _WIN32
    unsigned char* tmp = malloc(size);
#else
    unsigned char tmp[ size ];
#endif

    memcpy(tmp, left, size);
    memcpy(left, right, size);
    memcpy(right, tmp, size);

#if _WIN32
    free(tmp);
#endif
}

char* debug_buffer_to_string(const void* data, size_t size, size_t grouping, bool with_spaces)
{
    //if ((grouping < 1 || grouping > 8) || (grouping & (grouping - 1)) != 0)
    if ((grouping < 1 || grouping > 8))
    {
        grouping = 1;
    }

    size_t estimated_size = size * (with_spaces ? 2 : 1) * grouping * 2 + 2 + 1;
    char* s = (char*) malloc(estimated_size);

    if (s)
    {
        s[ 0 ] = '\0';
        strcat(s, "[");

        size_t i = 0;
        while (i < size)
        {
            char temp_buffer[ 2 + 1 ];

            for (size_t j = 0; j < grouping && (i + j) < size; j++)
            {
                unsigned char* b = (unsigned char*) data + i + j;
                snprintf(temp_buffer, sizeof(temp_buffer), "%02x", *b);
                temp_buffer[ 2 ] = '\0';
                strcat(s, temp_buffer);
            }

            if (with_spaces && i < (size - grouping)) strcat(s, " ");
            //if (newline_every != 0 && i % newline_every == 0) strcat(s, "\n");

            i += grouping;
        }

        strcat(s, "]");
        s[ estimated_size - 1 ] = '\0';
    }

    return s;
}

unsigned int rotate_bits_left(unsigned int value, int shift)
{
    if ((shift &= sizeof(value)*CHAR_BIT - 1) == 0)
    {
        return value;
    }
    return (value << shift) | (value >> (sizeof(value)*CHAR_BIT - shift));
}

unsigned int rotate_bits_right(unsigned int value, int shift)
{
    if ((shift &= sizeof(value)*CHAR_BIT - 1) == 0)
    {
        return value;
    }
    return (value >> shift) | (value << (sizeof(value)*CHAR_BIT - shift));
}
