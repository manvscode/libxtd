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
#include "utility.h"

#define FSM_STATE_UNINITIALIZED        (-1)


struct fsm {
    size_t max_states;

    fsm_state_t start_state;
    fsm_state_t end_state;

    fsm_state_t current_state;

    fsm_transition_table_t transitions;
    fsm_callbacks_table_t callbacks;
};


static inline fsm_state_t fsm_lookup_transition ( const fsm_t* fsm, fsm_event_t e );
static int fsm_transition_compare               ( const void* left, const void* right );


/*
 *   Create a finite state machine.
 */
fsm_t* fsm_create( size_t max_states, fsm_transition_table_t transitions, fsm_callbacks_table_t callbacks, fsm_state_t start, fsm_event_t end )
{
    fsm_t* fsm = malloc( sizeof(fsm_t) );

    if( fsm )
    {
        fsm->max_states    = max_states;
        fsm->start_state   = start;
        fsm->end_state     = end;
        fsm->current_state = start;
        fsm->transitions   = transitions;
        fsm->callbacks     = callbacks;

        qsort( fsm->transitions, fsm->max_states, sizeof(fsm_transition_t), fsm_transition_compare );
    }
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
    fsm->current_state = fsm->start_state;

    while( fsm->end_state != fsm->current_state )
    {
        fsm_state_fxn callback = fsm->callbacks[ fsm->current_state ];
        e = callback( data );

        fsm->current_state = fsm_lookup_transitions( fsm->current_state, e );
        assert( fsm->current_state != FSM_STATE_UNINITIALIZED );
    }
}

bool fsm_lookup_transition( const fsm_t* fsm, fsm_event_t e, fsm_state_t* next_state )
{
    #if 0 /* naive */
    fsm_state_t next_state = FSM_STATE_UNINITIALIZED;

    for( i = 0; i < fsm->max_states; i++ )
    {
        fsm_transition_t* transition = &fsm->transitions[ i ];

        if( transition->src_state == fsm->current_state && transition->event = e )
        {
            next_state = transition->dst_state;
            break;
        }
    }

    return next_state;
    #else
    fsm_transition_t key = { fsm->current_state, e, 0 };
    fsm_transition_t* t = bsearch( &key, fsm->transitions, fsm->max_states, sizeof(fsm_transition_t), fsm_transition_compare );
    return t ? t->dst_state : FSM_STATE_UNINITIALIZED;
    #endif
}

int fsm_transition_compare( const void* left, const void* right )
{
    fsm_transition_t* tl = left;
    fsm_transition_t* tr = right;
    int diff = tl->src_state - tr->src_state;
    return diff == 0 ? tl->event - tr->event : diff;
}
