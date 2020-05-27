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
#include <stdint.h>
#ifndef MOD_ADLER
#define MOD_ADLER 65521
#endif


uint32_t java_hash( const uint8_t* data, size_t len )
{
	uint32_t hash = 0;
	size_t i;

	for( i = 0; i < len; i++ )
	{
		hash = 31 * hash + data[ i ];
	}

	return hash;
}

uint32_t xor8( const uint8_t* data, size_t len )
{
	uint32_t lrc = 0;
	size_t index;

	for( index = 0; index < len; index++ )
	{
		lrc = (lrc + data[ index ]) & 0xFF;
	}

	return ((lrc ^ 0xFF) + 1) & 0xFF;
}

/* where data is the location of the data in physical memory and len is the length of the data in bytes */
uint32_t adler32( const uint8_t* data, size_t len )
{
	uint32_t a = 1, b = 0;
	size_t index;

	/* Process each byte of the data in order */
	for( index = 0; index < len; ++index )
	{
		a = (a + data[ index ]) % MOD_ADLER;
		b = (b + a) % MOD_ADLER;
	}

	return (b << 16) | a;
}

uint16_t fletcher16_simple( uint8_t* data, size_t len )
{
	uint16_t sum1 = 0;
	uint16_t sum2 = 0;
	size_t index;

	for( index = 0; index < len; ++index )
	{
		sum1 = (sum1 + data[ index ]) % 255;
		sum2 = (sum2 + sum1) % 255;
	}

	return (sum2 << 8) | sum1;
}

void fletcher16( uint8_t* check_a, uint8_t* check_b, uint8_t* data, size_t len )
{
	uint16_t sum1 = 0xff, sum2 = 0xff;

	while (len) {
		size_t tlen = len > 21 ? 21 : len;
		len -= tlen;
		do {
			sum1 += *data++;
			sum2 += sum1;
		} while (--tlen);
		sum1 = (sum1 & 0xff) + (sum1 >> 8);
		sum2 = (sum2 & 0xff) + (sum2 >> 8);
	}
	/* Second reduction step to reduce sums to 8 bits */
	sum1 = (sum1 & 0xff) + (sum1 >> 8);
	sum2 = (sum2 & 0xff) + (sum2 >> 8);
	*check_a = (uint8_t)sum1;
	*check_b = (uint8_t)sum2;
	return;
}

uint32_t fletcher32( uint16_t* data, size_t len )
{
	uint32_t sum1 = 0xffff, sum2 = 0xffff;

	while (len) {
		size_t tlen = len > 360 ? 360 : len;
		len -= tlen;
		do {
			sum1 += *data++;
			sum2 += sum1;
		} while (--tlen);
		sum1 = (sum1 & 0xffff) + (sum1 >> 16);
		sum2 = (sum2 & 0xffff) + (sum2 >> 16);
	}
	/* Second reduction step to reduce sums to 16 bits */
	sum1 = (sum1 & 0xffff) + (sum1 >> 16);
	sum2 = (sum2 & 0xffff) + (sum2 >> 16);
	return sum2 << 16 | sum1;
}

