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
#include <libcollections/array.h>
#include "utility.h"

typedef struct obs_observer_record {
	void* observer;
	obs_notify_fxn notify;
} obs_observer_record_t;


struct obs_subject {
	lc_array_t array;
	size_t size;
	size_t grow_amount;
};

obs_subject_t* obs_subject_create( size_t size, size_t grow_amount )
{
	obs_subject_t* subject = (obs_subject_t*) malloc( sizeof(obs_subject_t) );

	if( subject )
	{
		array_create( &subject->array, sizeof(obs_observer_record_t), size, malloc, free );
		subject->size        = 0;
		subject->grow_amount = grow_amount;
	}

	return subject;
}

void obs_subject_destroy( obs_subject_t** p_subject )
{
	if( p_subject )
	{
		array_destroy( &(*p_subject)->array );
		free( *p_subject );
		*p_subject = NULL;
	}
}

bool obs_subject_register( obs_subject_t* p_subject, void* observer, obs_notify_fxn notify )
{
	bool result = true;

	if( array_size( &p_subject->array ) >= p_subject->size )
	{
		result = array_resize( &p_subject->array, p_subject->size + p_subject->grow_amount );
	}

	if( result )
	{
		obs_observer_record_t* record = (obs_observer_record_t*) array_element( &p_subject->array, p_subject->size );

		record->observer = observer;
		record->notify   = notify;

		p_subject->size++;
	}

	return result;
}

void obs_subject_notify( const obs_subject_t* p_subject, void* user_data )
{
	for( size_t i = 0; i < p_subject->size; i++ )
	{
		obs_observer_record_t* record = (obs_observer_record_t*) array_element( (lc_array_t*) &p_subject->array, i );
		record->notify( record->observer, user_data );
	}
}

