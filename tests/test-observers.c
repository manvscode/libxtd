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
#include <string.h>
#include <time.h>
#include "utility.h"

static void notify_client( void* observer, void* user_data );

struct client {
	const char* name;
	size_t count;
} client_a = { "Socrates", 0 },
  client_b = { "Archimedes", 0 },
  client_c = { "Aristotle", 0 },
  client_d = { "Hippocrates", 0 };


int main( int argc, char *argv[] )
{
	obs_subject_t* subject = obs_subject_create( 0, 1 );

	obs_subject_register( subject, &client_a, notify_client );
	obs_subject_register( subject, &client_b, notify_client );
	obs_subject_register( subject, &client_c, notify_client );
	obs_subject_register( subject, &client_d, notify_client );

	srand( time(NULL) );

	size_t iterations = rand( ) % 45 + 2;

	while( iterations-- > 0 )
	{
		int r = rand();

		if( r % 7 == 0 )
		{
			obs_subject_notify( subject, "A modulus 7 event" );
		}
		if( r % 31 == 0 )
		{
			obs_subject_notify( subject, "A modulus 31 event" );
		}
	}

	obs_subject_destroy( &subject );
	return 0;
}


void notify_client( void* observer, void* user_data )
{
	struct client* p_client = (struct client*) observer;
	const char* message = user_data;
	p_client->count++;

	printf( "%s has been notified (count = %zd).  %s\n", p_client->name, p_client->count, message );
}
