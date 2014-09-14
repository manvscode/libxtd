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
//#define FSM_BENCH_MARK
#define FSM_HASH_TRANSITIONS
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#ifdef FSM_HASH_TRANSITIONS
#endif
#ifdef FSM_BENCH_MARK
#include <libcollections/bench-mark.h>
#endif
#include "utility.h"

#define FSM_STATE_UNINITIALIZED        NULL


struct fsm {
    size_t max_transitions;
    fsm_state_fxn start_state;
    fsm_state_fxn end_state;
    fsm_state_fxn current_state;
    fsm_transition_t* transitions;
	#ifdef FSM_HASH_TRANSITIONS
    fsm_transition_t** lookup_table;
	#endif
	#ifdef FSM_BENCH_MARK
	bench_mark_t bm;
	#endif
};

static void fsm_initialize ( fsm_t* fsm, size_t max_transitions, const fsm_transition_t* transitions, fsm_state_fxn start, fsm_state_fxn end );
static __inline fsm_state_fxn fsm_lookup_transition  ( const fsm_t* fsm, fsm_event_t e );
static __inline int           fsm_transition_compare ( const void* left, const void* right );
#ifdef FSM_HASH_TRANSITIONS
static size_t hash_transition( const fsm_transition_t* p_transition );
#endif

/*
 *   Create a finite state machine.
 */
fsm_t* fsm_create( size_t max_transitions, const fsm_transition_t* transitions, fsm_state_fxn start, fsm_state_fxn end )
{
    fsm_t* fsm = malloc( sizeof(fsm_t) );

    if( fsm )
    {
		fsm_initialize( fsm, max_transitions, transitions, start, end );
    }

	return fsm;
}

/*
 *   Initialize a finite state machine.
 */
void fsm_initialize( fsm_t* fsm, size_t max_transitions, const fsm_transition_t* transitions, fsm_state_fxn start, fsm_state_fxn end )
{
	fsm->max_transitions = max_transitions;
	fsm->start_state     = start;
	fsm->end_state       = end;
	fsm->current_state   = start;


	#ifdef FSM_COPY_TRANSITIONS
	fsm->transitions = malloc( sizeof(fsm_transition_t) * fsm->max_transitions );
	memcpy( fsm->transitions, transitions, sizeof(fsm_transition_t) * fsm->max_transitions );
	#else
	fsm->transitions = (fsm_transition_t*) transitions;
	#endif

	#ifdef FSM_HASH_TRANSITIONS
    fsm->lookup_table = malloc( sizeof(fsm_transition_t*) * fsm->max_transitions );
	memset( fsm->lookup_table, 0, sizeof(fsm_transition_t*) * fsm->max_transitions );
	for( size_t i = 0; i < fsm->max_transitions; i++ )
	{
		size_t index = hash_transition( &fsm->transitions[ i ] ) % fsm->max_transitions;
		while( fsm->lookup_table[ index ] )
		{
			index = (index + 1) % fsm->max_transitions;
		}
		assert( fsm->lookup_table[ index ] == NULL );
		fsm->lookup_table[ index ] = (fsm_transition_t*) &fsm->transitions[ i ];
	}
	#else
	qsort( (void*) fsm->transitions, fsm->max_transitions, sizeof(fsm_transition_t), fsm_transition_compare );
	#endif

	#ifdef FSM_BENCH_MARK
	fsm->bm = bench_mark_create( "FSM Transition" );
	#endif
}

/*
 *   Destroy a finite state machine.
 */
void fsm_destroy( fsm_t** fsm )
{
    if( fsm && *fsm )
    {
		#ifdef FSM_COPY_TRANSITIONS
		free( (*fsm)->transitions );
		#endif
		#ifdef FSM_BENCH_MARK
		bench_mark_destroy( (*fsm)->bm );
		#endif
		#ifdef FSM_HASH_TRANSITIONS
		free( (*fsm)->lookup_table );
		#endif
        free( *fsm );
        *fsm = NULL;
    }
}

/*
 *   Execute the finite state machine.
 */
void fsm_run( fsm_t* fsm, void* data )
{
	fsm_event_t e;
    fsm->current_state = fsm->start_state;

    while( fsm->end_state != fsm->current_state && fsm->current_state != FSM_STATE_UNINITIALIZED )
    {
		assert( fsm->current_state );
        e = fsm->current_state( data );

		#ifdef FSM_BENCH_MARK
		bench_mark_start( fsm->bm );
		#endif

        fsm->current_state = fsm_lookup_transition( fsm, e );

		#ifdef FSM_BENCH_MARK
		bench_mark_end( fsm->bm );
		bench_mark_report( fsm->bm );
		#endif

        assert( fsm->current_state != FSM_STATE_UNINITIALIZED );
    }
}

/*
 *   Execute the finite state machine from a loop.
 */
bool fsm_iterative_run( fsm_t* fsm, void* data )
{
	fsm_event_t e;
	bool done = fsm->end_state == fsm->current_state;

    if( !done && fsm->current_state != FSM_STATE_UNINITIALIZED )
    {
		assert( fsm->current_state );
        e = fsm->current_state( data );

		#ifdef FSM_BENCH_MARK
		bench_mark_start( fsm->bm );
		#endif
        fsm->current_state = fsm_lookup_transition( fsm, e );
		#ifdef FSM_BENCH_MARK
		bench_mark_end( fsm->bm );
		bench_mark_report( fsm->bm );
		#endif
        assert( fsm->current_state != FSM_STATE_UNINITIALIZED );
    }

	return done;
}

fsm_state_fxn fsm_lookup_transition( const fsm_t* fsm, fsm_event_t e )
{
	#ifdef FSM_HASH_TRANSITIONS
    fsm_transition_t key = { fsm->current_state, e, 0 };
	size_t index = hash_transition( &key ) % fsm->max_transitions;
	while( fsm_transition_compare( fsm->lookup_table[ index ], &key ) != 0 )
	{
		index = (index + 1) % fsm->max_transitions;
	}
	return fsm->lookup_table[ index ]->dst_state;
	#else
    fsm_transition_t key = { fsm->current_state, e, 0 };
    fsm_transition_t* t = bsearch( &key, fsm->transitions, fsm->max_transitions, sizeof(fsm_transition_t), fsm_transition_compare );
    return t ? t->dst_state : FSM_STATE_UNINITIALIZED;
	#endif
}

int fsm_transition_compare( const void* left, const void* right )
{
	#if 0
    const fsm_transition_t* tl = left;
    const fsm_transition_t* tr = right;
    int diff = (long) tl->src_state - (long) tr->src_state;
    return diff == 0 ? tl->event - tr->event : diff;
	#else
    const fsm_transition_t* tl = left;
    const fsm_transition_t* tr = right;
    return ((long) tl->src_state + tl->event) - ((long) tr->src_state + tr->event);
	#endif
}


#ifdef FSM_HASH_TRANSITIONS
size_t hash_transition( const fsm_transition_t* p_transition )
{
	#if 0
	const unsigned char *bytes = (const unsigned char*) p_transition;
	size_t size                = sizeof(fsm_state_fxn) + sizeof(fsm_event_t);
	size_t hash_code           = 0;
	size_t i;

	for( i = 0; i < size; i++ )
	{
		hash_code = 31 * hash_code + bytes[ i ];
	}

	return hash_code;
	#else
	return ((size_t)p_transition->src_state + p_transition->event) % SIZE_MAX;
	#endif
}
#endif
