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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include "utility.h"
#include "console.h"

int main( int argc, char *argv[] )
{
	const char* restrict moby_dick =
		"Call me Ishmael. Some years ago- never mind how long precisely- having little or no money in my purse, "
		"and nothing particular to interest me on shore, I thought I would sail about a little and see the watery "
		"part of the world. It is a way I have of driving off the spleen and regulating the circulation. Whenever "
		"I find myself growing grim about the mouth; whenever it is a damp, drizzly November in my soul; whenever "
		"I find myself involuntarily pausing before coffin warehouses, and bringing up the rear of every funeral I "
		"meet; and especially whenever my hypos get such an upper hand of me, that it requires a strong moral "
		"principle to prevent me from deliberately stepping into the street, and methodically knocking people's hats "
		"off- then, I account it high time to get to sea as soon as I can. This is my substitute for pistol and ball. "
		"With a philosophical flourish Cato throws himself upon his sword; I quietly take to the ship. There is nothing "
		"surprising in this. If they but knew it, almost all men in their degree, some time or other, cherish very "
		"nearly the same feelings towards the ocean with me.\n\n"
		"There now is your insular city of the Manhattoes, belted round by wharves as Indian isles by coral reefs- "
		"commerce surrounds it with her surf. Right and left, the streets take you waterward. Its extreme downtown is "
		"the battery, where that noble mole is washed by waves, and cooled by breezes, which a few hours previous "
		"were out of sight of land. Look at the crowds of water-gazers there.\n\n"
		"Circumambulate the city of a dreamy Sabbath afternoon. Go from Corlears Hook to Coenties Slip, and from thence, "
		"by Whitehall, northward. What do you see?--Posted like silent sentinels all around the town, stand thousands "
		"upon thousands of mortal men fixed in ocean reveries. Some leaning against the spiles; some seated upon the pier-"
		"heads; some looking over the bulwarks of ships from China; some high aloft in the rigging, as if striving to get "
		"a still better seaward peep. But these are all landsmen; of week days pent up in lath and plaster--tied to "
		"counters, nailed to benches, clinched to desks. How then is this? Are the green fields gone? What do they here?\n";
	char* restrict compressed = NULL;
	size_t compressed_size    = 0;
	char* restrict original   = NULL;
	size_t original_size      = 0;


    console_fg_color_8( stdout, CONSOLE_COLOR8_CYAN );
	console_print_divider( stdout, "[ Moby Dick ]" );
	size_t moby_dick_size = strlen(moby_dick) + 1;
	printf( "%s\n", moby_dick );
    console_fg_bright_color_8( stdout, CONSOLE_COLOR8_CYAN );
	console_print_divider( stdout, "[ Before Encoding ]" );

	for( size_t i = 0; i < moby_dick_size; i++ )
	{
		printf( "%02x", (uint8_t) moby_dick[ i ] );
	}
	printf( " (%ld bytes)\n", moby_dick_size );

	if( huffman_encode( moby_dick, moby_dick_size, (void**) &compressed, &compressed_size ) )
	{
        console_fg_color_8( stdout, CONSOLE_COLOR8_MAGENTA );
		console_print_divider( stdout, "[ Huffman Encoded ]" );

		size_t header_size = sizeof(size_t) + (UCHAR_MAX + 1 );
		for( size_t i = header_size; i < compressed_size; i++ )
		{
			printf( "%02x", (uint8_t) compressed[ i ] );
		}
		printf( " (%ld header bytes + %ld bytes = %ld total bytes)\n", header_size, compressed_size - header_size, compressed_size );
	}

	if( huffman_decode( compressed, compressed_size, (void**) &original, &original_size ) )
	{
        console_fg_bright_color_8( stdout, CONSOLE_COLOR8_BLUE );
		console_print_divider( stdout, "[ Huffman Decoded ]" );
		printf( "%s\n", original );

		for( size_t i = 0; i < original_size; i++ )
		{
			printf( "%02x", (uint8_t) original[ i ] );
		}
		printf( " (%ld bytes)\n", original_size );
	}
    console_reset(stdout);

	free( compressed );
	free( original );
	return 0;
}
