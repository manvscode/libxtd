#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <libcollections/bheap.h>
#include <libcollections/vector.h>
#include "utility.h"

#define ASCII_COUNT   (UCHAR_MAX + 1)   /* 256 possible ascii characters */

typedef struct huffman_code {
	uint16_t code;
	uint16_t size;
	bool     used;
} huffman_code_t;

typedef struct huffman_node {
	uint8_t symbol;
	uint8_t frequency; /* scaled value */

	struct huffman_node* left;
	struct huffman_node* right;
	struct huffman_node* parent;
} huffman_node_t;

static inline void huffman_build_tree             ( huffman_node_t** root, size_t* frequencies );
static inline void huffman_build_codes            ( huffman_node_t* root, huffman_code_t* codes, uint16_t code, uint16_t size );
static inline huffman_node_t* huffman_node_create ( uint8_t symbol, size_t frequency, huffman_node_t* left, huffman_node_t* right, huffman_node_t* parent );
static inline void huffman_node_destroy           ( huffman_node_t** node );
#ifndef max
#define _max( x, y )              ((x) ^ (((x) ^ (y)) & -((x) < (y))))
#endif

bool huffman_encode( const void* restrict _original, size_t size, void** restrict compressed, size_t* compressed_size )
{
	const unsigned char* restrict original   = _original;

	if( !original )
	{
		*compressed = NULL;
		return false;
	}
	
	size_t frequency_table[ ASCII_COUNT ] = { 0 };

	for( size_t i = 0; i < size; i++ )
	{
		uint8_t currentByte = original[ i ];
		frequency_table[ currentByte ]++;
	}


	size_t max = 0;
	for( uint8_t symbol = 0; symbol <  ASCII_COUNT; symbol++ )
	{
		max = _max( frequency_table[ symbol ], max );
	}

	for( uint8_t symbol = 0; symbol < ASCII_COUNT; symbol++ )
	{
		uint8_t scaled_freq = UCHAR_MAX * (frequency_table[ symbol ] / ((double)max));

		if( scaled_freq == 0 && frequency_table[ symbol ] != 0 )
		{
			scaled_freq = 1;
		}

		frequency_table[ symbol ] = scaled_freq;
	}


	huffman_node_t* root = NULL;
	huffman_build_tree( &root, frequency_table );

	huffman_code_t codes[ ASCII_COUNT ];
	memset( codes, 0, sizeof(huffman_code_t) * ASCII_COUNT );

	huffman_build_codes( root, codes, 0, 0 );
	huffman_node_destroy( &root );

	size_t header_size = sizeof(size_t) + sizeof(uint8_t) * ASCII_COUNT;

	unsigned char* _compressed = (unsigned char*) malloc( header_size );
	*compressed_size = header_size;

	if( _compressed )
	{
		return false;
	}

	memcpy( _compressed, &size, sizeof(size_t) );

	for( size_t i = sizeof(size_t); i < header_size; i++ )
	{
		_compressed[ i ] = frequency_table[ i ];
	}


	size_t output_bits = CHAR_BIT * header_size;
	// compress the data	
	for( size_t i = 0; i < size; i++ )
	{

		uint8_t symbol = original[ i ];
		huffman_code_t code = codes[ symbol ];

		assert( code.used && code.size > 0 );


		for( size_t b = 0; b < code.size; b++ )
		{
			if( output_bits % CHAR_BIT == 0 )
			{
				size_t new_size = output_bits / CHAR_BIT + 1;
				void *new_buffer = (void*) realloc( _compressed, new_size );
				*compressed_size = new_size;

				if( new_buffer )
				{
					free( _compressed );
					return false;
				}
			}

			bool is_on = code.code & (1 << (code.size - b));
			_compressed[ output_bits / CHAR_BIT ] |=  is_on << (output_bits % CHAR_BIT);
		}
		
	}	

	*compressed = _compressed;

	return true;
}

bool huffman_decode( const void* restrict compressed, size_t compressed_size, void** restrict original, size_t* size )
{

	return true;
}

static int node_compare( const void* restrict p_data_left, const void* restrict p_data_right )
{
	const huffman_node_t* left  = p_data_left;
	const huffman_node_t* right = p_data_right;

	/* smallest to largest */
	return left->frequency - right->frequency;
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


void huffman_build_tree( huffman_node_t** root, size_t* frequencies )
{
	pbheap_t heap;
	pbheap_create( &heap, ASCII_COUNT, node_compare, malloc, free );

	for( uint8_t symbol = 0; symbol < ASCII_COUNT; symbol++ )
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


void huffman_build_codes( huffman_node_t* root, huffman_code_t* codes, uint16_t code, uint16_t size )
{
	if( !root->left && !root->right ) // leaf node
	{
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
			huffman_build_codes( root->left, codes, code << 1 | 0x0001, size + 1 );
		}
	}
}
