/*
 * Copyright (C) 2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#include <stdio.h>
#include <string.h>
#include "utility.h"


int main( int argc, char *argv[] )
{
#if 0
	const char* input = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
#else
	const char* input = "any carnal pleas";
#endif
	size_t input_len = strlen(input);

	size_t base64_encoded_len = 0;
	char* base64_encoded = base64_encode( input, input_len + 1, &base64_encoded_len );

	if( base64_encoded )
	{
		size_t original_size = 0;
		char* original = base64_decode( base64_encoded, base64_encoded_len, &original_size );

		printf( "   Input: %s (len = %lu)\n", input, input_len + 1 );
		printf( "  Base64: %s (len = %lu)\n", base64_encoded, base64_encoded_len );
		printf( "Original: %s (len = %lu)\n", original, original_size );
	}


	return  0;
}
