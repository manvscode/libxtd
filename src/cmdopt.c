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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "xtd/cmdopt.h"


cmd_opt_result_t cmd_opt_process(
	int argc, char* argv[],
	const cmd_opt_t* options, size_t option_count,
	cmd_opt_error_t on_error, void* user_data )
{
	cmd_opt_result_t result = CMD_OPT_SUCCESS;

	if( argc <= 1 )
	{
		result = CMD_OPT_ERR_NO_OPTIONS;
		on_error( user_data, result, NULL );
		goto done;
	}

	for( int arg = 1; arg < argc; arg++ )
	{
		const cmd_opt_t* option = cmd_opt_find( options, option_count, argv[ arg ] );
		bool is_processed = false;

		if( option )
		{
			// Does this option expect arguments
			if( option->opt_arg_count > 0 )
			{
				if( (arg + option->opt_arg_count) < argc )
				{
					// has the arguments
					if( !option->callback( user_data, (const char**) &argv[arg + 1], option->opt_arg_count ) )
					{
						result = CMD_OPT_ERR_ABORTED;
						on_error( user_data, result, argv[arg] );
						goto done;
					}
				}
				else
				{
					result = CMD_OPT_ERR_INVALID_ARG_COUNT;
					on_error( user_data, result, argv[arg] );
					goto done;
				}

				arg += option->opt_arg_count;
			}
			else // This is a boolean option
			{
				if( !option->callback( user_data, NULL, 0 ) )
				{
					result = CMD_OPT_ERR_ABORTED;
					on_error( user_data, result, argv[arg] );
					goto done;
				}
			}

			is_processed = true;
		}

		if( !is_processed )
		{
			result = CMD_OPT_ERR_UNEXPECTED_OPTION;
			on_error( user_data, result, argv[arg] );
			goto done;
		}
	}

done:
	return result;
}

void cmd_opt_help( const cmd_opt_t* options, size_t option_count )
{
	for( int o = 0; o < option_count; o++ )
	{
		const cmd_opt_t* opt = &options[ o ];
		printf( "  %3.3s, %-20.20s   %-48.48s\n", opt->opt_short, opt->opt_long, opt->opt_description );
	}
}

const cmd_opt_t* cmd_opt_find( const cmd_opt_t* options, size_t option_count, const char* argv )
{
	const cmd_opt_t* result = NULL;

	for( int o = 0; !result && o < option_count; o++ )
	{
		const cmd_opt_t* option = &options[ o ];
		if( strcmp( option->opt_short, argv ) == 0 || strcmp( option->opt_long, argv ) == 0 )
		{
			result = option;
		}
	}

	return result;
}


bool cmd_opt_nop( void* user_data, const char* arguments[], size_t count )
{
	return true;
}
