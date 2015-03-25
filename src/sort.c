#include <stddef.h>
#include <stdbool.h>
#include <string.h>


void bubble_sort( void *base, size_t nel, size_t width, int (*compare)(const void *, const void *) )
{
	if( nel >= 2 )
	{
		bool swapped = true;

		while( swapped )
		{
			swapped = false;
			for( size_t i = 1; i < nel; i++ )
			{
				void* left  = ((unsigned char*)base) + (i    ) * width;
				void* right = ((unsigned char*)base) + (i - 1) * width;

				if( compare( left, right ) < 0 )
				{
					unsigned char tmp[ width ];

					memcpy( tmp, left, width );
					memcpy( left, right, width );
					memcpy( right, tmp, width );

					swapped = true;
				}
			}
		}
	}
}
