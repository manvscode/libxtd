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
#include <assert.h>
#include "utility.h"

#define FSM_STATE_UNINITIALIZED        NULL


struct fsm {
    size_t max_transitions;
    fsm_state_fxn start_state;
    fsm_state_fxn end_state;
    fsm_state_fxn current_state;
    fsm_transition_t* transitions;
};


static fsm_state_fxn fsm_lookup_transition  ( const fsm_t* fsm, fsm_event_t e );
static int           fsm_transition_compare ( const void* left, const void* right );


/*
 *   Create a finite state machine.
 */
fsm_t* fsm_create( size_t max_transitions, fsm_transition_t* transitions, fsm_state_fxn start, fsm_state_fxn end )
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
void fsm_initialize( fsm_t* fsm, size_t max_transitions, fsm_transition_t* transitions, fsm_state_fxn start, fsm_state_fxn end )
{
	fsm->max_transitions = max_transitions;
	fsm->start_state     = start;
	fsm->end_state       = end;
	fsm->current_state   = start;
	fsm->transitions     = transitions;

	qsort( fsm->transitions, fsm->max_transitions, sizeof(fsm_transition_t), fsm_transition_compare );
}

/*
 *   Destroy a finite state machine.
 */
void fsm_destroy( fsm_t** fsm )
{
    if( fsm && *fsm )
    {
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

        fsm->current_state = fsm_lookup_transition( fsm, e );
        assert( fsm->current_state != FSM_STATE_UNINITIALIZED );
    }
}

fsm_state_fxn fsm_lookup_transition( const fsm_t* fsm, fsm_event_t e )
{
    fsm_transition_t key = { fsm->current_state, e, 0 };
    fsm_transition_t* t = bsearch( &key, fsm->transitions, fsm->max_transitions, sizeof(fsm_transition_t), fsm_transition_compare );
    return t ? t->dst_state : FSM_STATE_UNINITIALIZED;
}

int fsm_transition_compare( const void* left, const void* right )
{
    const fsm_transition_t* tl = left;
    const fsm_transition_t* tr = right;
    int diff = (long) tl->src_state - (long) tr->src_state;
    return diff == 0 ? tl->event - tr->event : diff;
}
