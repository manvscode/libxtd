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
#include <stdlib.h>
#include <stdbool.h>
#include "libxtd-config.h"

typedef union two_bytes {
    unsigned short s;
    unsigned char bytes[ 2 ];
} two_bytes_t;


bool is_big_endian(void)
{
    two_bytes_t check;
    check.s = 1;

    if (check.bytes[ 0 ] == 1)
    {
        return false; /* little endian */
    }

    return true;
}

void swap_every_two_bytes(void* mem, size_t size)
{
    unsigned char* buffer = (unsigned char*) mem;

    /* If we have an odd number of bytes, then
     * we subtract 1 and swap up until that size.
     */
    size -= (size % 2);

    for (size_t i = 0; i < size - 1; i += 2)
    {
        unsigned char tmp = buffer[ i ];
        buffer[ i ] = buffer[ i + 1];
        buffer[ i + 1 ] = tmp;
    }
}

void hton(void* mem, size_t size)
{
#ifndef WORDS_BIGENDIAN
    if (!is_big_endian())
    {
        swap_every_two_bytes(mem, size);
    }
#endif
}

void ntoh(void* mem, size_t size)
{
#ifndef WORDS_BIGENDIAN
    if (!is_big_endian())
    {
        swap_every_two_bytes(mem, size);
    }
#endif
}
