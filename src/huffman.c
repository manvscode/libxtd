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
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <libcollections/bheap.h>
#ifdef DEBUG_HUFFMAN
#include <stdio.h>
#include <math.h>
#endif
#include "utility.h"

#define ASCII_COUNT   (UCHAR_MAX + 1)   /* 256 possible ascii characters */
#ifndef max
#define _max( x, y )              ((x) ^ (((x) ^ (y)) & -((x) < (y))))
#endif

typedef struct huffman_code {
	uint16_t code;
	uint16_t size;
	uint16_t used;
} huffman_code_t;

typedef struct huffman_node {
	uint8_t symbol;
	size_t frequency; /* scaled value */

	struct huffman_node* left;
	struct huffman_node* right;
	struct huffman_node* parent;
} huffman_node_t;

static __inline void            huffman_build_tree    ( huffman_node_t** root, uint8_t frequencies[] );
static __inline void            huffman_build_codes   ( huffman_node_t* root, huffman_code_t codes[], uint16_t code, uint16_t size );
static __inline int             huffman_node_compare  ( const void* __restrict p_data_left, const void* __restrict p_data_right );
static __inline huffman_node_t* huffman_node_create   ( uint8_t symbol, size_t frequency, huffman_node_t* left, huffman_node_t* right, huffman_node_t* parent );
static __inline void            huffman_node_destroy  ( huffman_node_t** node );


bool huffman_encode( const void* __restrict _original, size_t original_size, void** __restrict _compressed, size_t* compressed_size )
{
	const unsigned char* __restrict original = _original;
	uint8_t frequency_table[ ASCII_COUNT ] = { 0 };
	size_t max = 1;

	if( !original )
	{
		*_compressed = NULL;
		return false;
	}

	for( size_t i = 0; i < original_size; i++ )
	{
		uint8_t currentByte = original[ i ];
		frequency_table[ currentByte ]++;
	}


	for( size_t symbol = 0; symbol <  ASCII_COUNT; symbol++ )
	{
		#if 0
		max = _max( frequency_table[ symbol ], max );
		#else
		if( frequency_table[ symbol ] > max )
		{
			max = frequency_table[ symbol ];
		}
		#endif
	}

	for( size_t symbol = 0; symbol < ASCII_COUNT; symbol++ )
	{
		uint8_t scaled_freq = UCHAR_MAX * (frequency_table[ symbol ] / ((double)max));

		if( scaled_freq == 0 && frequency_table[ symbol ] != 0 )
		{
			scaled_freq = 1;
		}

		frequency_table[ symbol ] = scaled_freq;

		#ifdef DEBUG_HUFFMAN_FREQUENCY_TABLE
		printf( "%lu := %d\n", symbol, scaled_freq );
		#endif
	}


	huffman_node_t* root = NULL;
	huffman_build_tree( &root, frequency_table );

	huffman_code_t codes[ ASCII_COUNT ];
	memset( codes, 0, sizeof(huffman_code_t) * ASCII_COUNT );

	huffman_build_codes( root, codes, 0, 0 );
	huffman_node_destroy( &root );

	size_t header_size = sizeof(size_t) + sizeof(uint8_t) * ASCII_COUNT;

	unsigned char* compressed = (unsigned char*) malloc( header_size );
	*compressed_size = header_size;

	if( !compressed )
	{
		return false;
	}

	memcpy( compressed, &original_size, sizeof(size_t) );

	size_t start_of_freq_table = sizeof(size_t);
	for( size_t i = start_of_freq_table; i < header_size; i++ )
	{
		compressed[ i ] = frequency_table[ i - start_of_freq_table ];
	}

	#ifdef DEBUG_HUFFMAN_CODES
	size_t total_entropy = 0;
	for( size_t i = 0; i < original_size; i++ )
	{
		uint8_t symbol      = original[ i ];
		huffman_code_t code = codes[ symbol ];

		printf( "code = %#06x %10s (%d bits)\n", code.code, byte_to_binary(code.code), code.size );
		total_entropy += code.size;
	}
	printf( "Compressed to %ld bytes (%ld bits used)\n", (long) ceil(total_entropy / ((double)CHAR_BIT)), total_entropy );
	#endif

	size_t output_bits = CHAR_BIT * header_size;

	for( size_t i = 0; i < original_size; i++ )
	{
		uint8_t symbol      = original[ i ];
		huffman_code_t code = codes[ symbol ];

		assert( code.used && code.size > 0 );

		for( size_t b = 0; b < code.size; b++ )
		{
			if( output_bits % CHAR_BIT == 0 ) // enlarge buffer
			{
				size_t new_size  = (output_bits / CHAR_BIT) + 1;
				void *new_buffer = (void*) realloc( compressed, new_size );

				if( !new_buffer )
				{
					free( compressed );
					return false;
				}
				else
				{
					compressed = new_buffer;
					*compressed_size = new_size;
					compressed[ new_size - 1 ] = 0;
				}
			}

			bool is_on = code.code & (1 << (code.size - 1 - b));
			#ifdef DEBUG_HUFFMAN
			printf( is_on ? "1" : "0" );
			#endif

			if( is_on )
			{
				assert( (output_bits / CHAR_BIT) < *compressed_size );
				compressed[ output_bits / CHAR_BIT ] |=  (0x80 >> output_bits % CHAR_BIT);
			}
			else
			{
				assert( (output_bits / CHAR_BIT) < *compressed_size );
				compressed[ output_bits / CHAR_BIT ] &=  ~(0x80 >> (output_bits % CHAR_BIT));
			}

			output_bits++;
		}
		#ifdef DEBUG_HUFFMAN
		printf( " " );
		#endif

	}
	#ifdef DEBUG_HUFFMAN
	printf( "\n" );
	#endif

	*_compressed = compressed;

	return true;
}

bool huffman_decode( const void* __restrict _compressed, size_t compressed_size, void** __restrict _original, size_t* original_size )
{
	const unsigned char* __restrict compressed = _compressed;
	uint8_t frequency_table[ ASCII_COUNT ] = { 0 };

	if( !compressed )
	{
		*_original = NULL;
		return false;
	}

	memcpy( original_size, compressed, sizeof(size_t) );

	unsigned char* __restrict original = (unsigned char*) malloc( *original_size + 1 );

	if( !original )
	{
		*_original = NULL;
		return false;
	}

	size_t header_size         = sizeof(size_t) + sizeof(uint8_t) * ASCII_COUNT;
	size_t start_of_freq_table = sizeof(size_t);

	for( size_t i = start_of_freq_table; i < header_size; i++ )
	{
		frequency_table[ i - start_of_freq_table ] = compressed[ i ];

		#ifdef DEBUG_HUFFMAN_FREQUENCY_TABLE
		printf( "%lu := %d\n", i - start_of_freq_table, frequency_table[ i - start_of_freq_table ] );
		#endif
	}

	huffman_node_t* root = NULL;
	huffman_build_tree( &root, frequency_table );

	#ifdef DEBUG_HUFFMAN_CODES
	huffman_code_t codes[ ASCII_COUNT ];
	memset( codes, 0, sizeof(huffman_code_t) * ASCII_COUNT );
	huffman_build_codes( root, codes, 0, 0 );
	size_t total_entropy = 0;
	for( size_t i = 0; i < ASCII_COUNT; i++ )
	{
		huffman_code_t code = codes[ i ];
		printf( "code = %#06x %10s (%d bits)\n", code.code, byte_to_binary(code.code), code.size );
		total_entropy += code.size;
	}
	#endif

	size_t original_position = 0;
	size_t last_bit = compressed_size * CHAR_BIT;
	size_t bit = header_size * CHAR_BIT;

	while( bit < last_bit )
	{
		huffman_node_t* tree = root;

		while( tree && tree->left && tree->right )
		{
			if( bit >= last_bit )
			{
				tree = NULL;
				break;
			}

			assert( (bit / CHAR_BIT) < compressed_size );
			bool is_on = compressed[ (bit / CHAR_BIT) ] & (0x80 >> (bit % CHAR_BIT));

			if( is_on )
			{
				tree = tree->right;
			}
			else
			{
				tree = tree->left;
			}

			bit++;
			assert( tree );
		}

		if( tree )
		{
			assert( original_position < *original_size );
			original[ original_position++ ] = tree->symbol;
		}
	}

	*_original = original;

	huffman_node_destroy( &root );
	return true;
}

int huffman_node_compare( const void* __restrict p_data_left, const void* __restrict p_data_right )
{
	const huffman_node_t* left  = p_data_left;
	const huffman_node_t* right = p_data_right;

	/* smallest to largest */
	return right->frequency - left->frequency;
}

huffman_node_t* huffman_node_create( uint8_t symbol, size_t frequency, huffman_node_t* left, huffman_node_t* right, huffman_node_t* parent )
{
	huffman_node_t* node = (huffman_node_t*) malloc( sizeof(huffman_node_t) );

	if( node )
	{
		node->symbol    = symbol;
		node->frequency = frequency;
		node->left      = left;
		node->right     = right;
		node->parent    = parent;
	}

	return node;
}

void huffman_node_destroy( huffman_node_t** node )
{
	if( (*node)->left )
	{
		huffman_node_destroy( &(*node)->left );
	}

	if( (*node)->right )
	{
		huffman_node_destroy( &(*node)->right );
	}

	free( *node );
	*node = NULL;
}

void huffman_build_tree( huffman_node_t** root, uint8_t frequencies[] )
{
	pbheap_t heap;
	pbheap_create( &heap, ASCII_COUNT, huffman_node_compare, malloc, free );

	for( size_t symbol = 0; symbol < ASCII_COUNT; symbol++ )
	{
		if( frequencies[symbol] > 0 )
		{
			huffman_node_t* node = huffman_node_create( symbol, frequencies[symbol], NULL, NULL, NULL );
			pbheap_push( &heap, node );
		}
	}

	while( pbheap_size( &heap ) > 1 )
	{
		huffman_node_t* node1 = pbheap_peek( &heap );
		pbheap_pop( &heap );

		huffman_node_t* node2 = pbheap_peek( &heap );
		pbheap_pop( &heap );

		huffman_node_t* new_node = huffman_node_create( 0, node1->frequency + node2->frequency, node1, node2, NULL );
		node1->parent = new_node;
		node2->parent = new_node;

		pbheap_push( &heap, new_node );
	}

	*root = pbheap_peek( &heap );
	pbheap_pop( &heap );

	assert( pbheap_size(&heap) == 0 );

	pbheap_destroy( &heap );
}

void huffman_build_codes( huffman_node_t* root, huffman_code_t codes[], uint16_t code, uint16_t size )
{
	static size_t count = 0;

	if( !root->left && !root->right ) // leaf node
	{
		count++;

		assert( root->symbol >= 0 && root->symbol < ASCII_COUNT );


		#ifdef DEBUG_HUFFMAN
		if( root->symbol == '\0' )
		{
			printf( "'\\0' --> %s\n", byte_to_binary(code) );
		}
		else
		{
			printf( " '%c' --> %s\n", root->symbol, byte_to_binary(code) );
		}
		#endif

		codes[ root->symbol ].code = code;
		codes[ root->symbol ].size = size;
		codes[ root->symbol ].used = true;
	}
	else // not a leaf node
	{
		if( root->left )
		{
			/* add a 0 to the code */
			huffman_build_codes( root->left, codes, code << 1, size + 1 );
		}

		if( root->right )
		{
			/* add a 1 to the code */
			huffman_build_codes( root->right, codes, code << 1 | 0x0001, size + 1 );
		}
	}
}
