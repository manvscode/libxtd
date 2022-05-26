/*
 * Copyright (C) 2010-2022 by Joseph A. Marrero. https://joemarrero.com/
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
#include "xtd/refobj.h"

#if defined(__MINGW32__) || defined(__MINGW64)
# include <stdint.h>
# ifndef size_t
typedef ptrdiff_t ssize_t;
# endif
#elif defined(_WIN32) || defined(_WIN64)
# include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
# include <sys/types.h>
#endif

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

