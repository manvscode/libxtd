#ifdef __linux__
#include <sys/types.h>
#endif
#include <stdlib.h>
#include "xtd/refobj.h"

typedef struct refobj {
	void (*destroy) ( void* ptr );
	ssize_t count;
} refobj_t;

#define refobj_data( r )         ((void*)( ((char*)r) + sizeof(refobj_t) ))
#define refobj_base( d )         ((refobj_t*)( ((char*)d) - sizeof(refobj_t) ))

void* refobj_alloc( size_t size, void (*destroy) ( void* ptr ) )
{
	refobj_t* r = malloc( sizeof(refobj_t) + size );

	if( r )
	{
		r->destroy = destroy;
		r->count   = 1;
	}

	return refobj_data( r );
}

void refobj_retain( void* o )
{
	refobj_t* obj = refobj_base( o );
	obj->count += 1;
}

void refobj_release( void* o )
{
	refobj_t* obj = refobj_base( o );
	obj->count -= 1;

	if( obj->count == 0 )
	{
		obj->destroy( refobj_data(obj) );
		free( obj );
	}
}

