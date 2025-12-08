/*
 * Copyright (C) 2014-2025 by Joseph A. Marrero. https://joemarrero.com/
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
#include <string.h>
#include <assert.h>
#include <stdio.h>

static const char base64_symbol_table[ 64 ] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/',
};

static inline char char_at(const void* in, size_t index)
{
    return ((char*)in)[ index ];
}


static inline int get_index(char c)
{
    int index = -1;

    for (int i = 0; i < 64; i++)
    {
        if (c == base64_symbol_table[ i ])
        {
            index = i;
        }
    }

    return index;
}

char* base64_encode(const void* in, size_t in_size, size_t* out_len)
{
    char* output = NULL;

    if (in && in_size > 0)
    {
        size_t padding = (in_size % 3);
        *out_len = 4 * (in_size + (padding > 0 ? (3 - padding) : 0)) / 3;

        output = malloc(*out_len + 1);

        if (output)
        {
            for (size_t i = 0, o = 0; o < *out_len; i += 3, o += 4)
            {
                char a = char_at(in, i + 0);
                size_t w = (a & ~0x03) >> 2;
                output[ o + 0 ] = base64_symbol_table[ w ];

                if (i + 1 < in_size)
                {
                    char b = char_at(in, i + 1);
                    size_t x = ((a & 0x03) << 4) | ((b & 0xf0) >> 4);
                    output[ o + 1 ] = base64_symbol_table[ x ];

                    if (i + 2 < in_size)
                    {
                        char c = char_at(in, i + 2);
                        size_t y = ((b & 0x0f) << 2) | ((c & 0xc0) >> 6);
                        size_t z = (c & 0x3f);

                        output[ o + 2 ] = base64_symbol_table[ y ];
                        output[ o + 3 ] = base64_symbol_table[ z ];
                    }
                    else
                    {
                        size_t y = (b & 0x0f) << 2;

                        output[ o + 2 ] = base64_symbol_table[ y ];
                        output[ o + 3 ] = '=';

                    }
                }
                else
                {
                    size_t x = (a & 0x03) << 4;
                    output[ o + 1 ] = base64_symbol_table[ x ];
                    output[ o + 2 ] = '=';
                    output[ o + 3 ] = '=';
                }
            }

            output[ *out_len ] = '\0';
        }
        else
        {
            *out_len = 0;
        }
    }
    else
    {
        *out_len = 0;
    }

    return output;
}

void* base64_decode(const char* in, size_t in_len, size_t* out_len)
{
    unsigned char* output = NULL;

    if (in_len % 4 == 0)
    {
        char* equal_sign = strchr(in, '=');
        *out_len = ((in_len * 3) / 4) - (equal_sign ? (in + in_len - equal_sign) : 0);

        output = malloc(*out_len + 1);

        if (output)
        {
            for (size_t i = 0, j = 0; i < in_len; i += 4)
            {
                int w = get_index(in[i + 0]);
                int x = get_index(in[i + 1]);
                int y = get_index(in[i + 2]);
                int z = get_index(in[i + 3]);

                output[ j++ ] = (w << 2) | (x >> 4);

                if (y >= 0 && y < 64)
                {
                    output[ j++ ] = (x << 4) | (y >> 2);

                    if (z >= 0 && z < 64)
                    {
                        output[ j++ ] = (y << 6) | z;
                    }
                }
            }

            output[ *out_len ] =  '\0';
        }
        else
        {
            out_len = 0;
        }
    }
    else
    {
        out_len = 0;
    }

    return output;
}
