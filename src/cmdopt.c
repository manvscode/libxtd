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
#include <math.h>
#include <assert.h>
#include "xtd/cmdopt.h"

struct cmd_opt_ctx {
	int argc;
	const char** argv;
	int opt_args_count;
	const char** opt_args;
};

int cmd_opt_argc( const cmd_opt_ctx_t* ctx )
{
	return ctx->argc;
}

const char** cmd_opt_argv( const cmd_opt_ctx_t* ctx )
{
	return ctx->argv;
}

size_t cmd_opt_args_count( const cmd_opt_ctx_t* ctx )
{
	return ctx->opt_args_count;
}

const char** cmd_opt_args( const cmd_opt_ctx_t* ctx )
{
	return ctx->opt_args;
}

cmd_opt_result_t cmd_opt_process(
	int argc, char* argv[],
	const cmd_opt_t* options, size_t option_count,
	cmd_opt_error_t on_error, cmd_opt_handler_t on_unexpected,
	void* user_data )
{
	assert( argv && "Command line arguments cannot be null." );
	assert( options && "Options cannot be null." );
	cmd_opt_result_t result = CMD_OPT_SUCCESS;

	if( argc <= 1 )
	{
		result = CMD_OPT_ERR_NO_OPTIONS;
		if( on_error ) on_error( result, NULL, user_data );
		goto done;
	}

	for( int arg = 1; arg < argc; arg++ )
	{
		bool is_processed = false;

		// Look for an explicit option.
		const cmd_opt_t* option = cmd_opt_find( options, option_count, argv[ arg ] );

		if( option )
		{
			// Does this option expect arguments?
			if( option->opt_arg_count > 0 )
			{
				if( (arg + option->opt_arg_count) < argc )
				{
					cmd_opt_ctx_t ctx = (cmd_opt_ctx_t) {
						.argc = argc,
						.argv = (const char**) argv,
						.opt_args_count = option->opt_arg_count,
						.opt_args = (const char**) &argv[ arg + 1 ],
					};

					// has the arguments
					if( !option->callback( &ctx, user_data ) )
					{
						result = CMD_OPT_ERR_ABORTED;
						if( on_error ) on_error( result, argv[arg], user_data );
						goto done;
					}
				}
				else
				{
					result = CMD_OPT_ERR_INVALID_ARG_COUNT;
					if( on_error ) on_error( result, argv[arg], user_data );
					goto done;
				}

				arg += option->opt_arg_count;
			}
			else // This is a boolean option
			{
				cmd_opt_ctx_t ctx = (cmd_opt_ctx_t) {
					.argc = argc,
					.argv = (const char**) argv,
					.opt_args_count = 0,
					.opt_args = NULL,
				};

				if( !option->callback( &ctx, user_data ) )
				{
					result = CMD_OPT_ERR_ABORTED;
					if( on_error ) on_error( result, argv[arg], user_data );
					goto done;
				}
			}

			is_processed = true;
		}

		if( !is_processed && on_unexpected )
		{
			cmd_opt_ctx_t ctx = (cmd_opt_ctx_t) {
				.argc = argc,
				.argv = (const char**) argv,
				.opt_args_count = 1,
				.opt_args = (const char**) &argv[ arg ],
			};

			// has the arguments
			if( !on_unexpected( &ctx, user_data ) )
			{
				result = CMD_OPT_ERR_ABORTED;
				if( on_error ) on_error( result, argv[arg], user_data );
				goto done;
			}

			is_processed = true;
		}

		if( !is_processed )
		{
			result = CMD_OPT_ERR_UNEXPECTED_OPTION;
			if( on_error ) on_error( result, argv[arg], user_data );
			goto done;
		}
	}

done:
	return result;
}

void cmd_opt_print_help( const cmd_opt_t* options, size_t option_count )
{
	assert( options && "Options cannot be null." );
	for( int o = 0; o < option_count; o++ )
	{
		const cmd_opt_t* opt = &options[ o ];
		if( opt->opt_short && opt->opt_long && opt->opt_description )
		{
			printf( "  %3.3s, %-20.20s   %-48.48s\n", opt->opt_short, opt->opt_long, opt->opt_description );
		}
	}
}

const cmd_opt_t* cmd_opt_find( const cmd_opt_t* options, size_t option_count, const char* argv )
{
	assert( options && "Options cannot be null." );
	const cmd_opt_t* result = NULL;

	for( int o = 0; !result && o < option_count; o++ )
	{
		const cmd_opt_t* option = &options[ o ];
		if( argv ) // explict option
		{
			if( (option->opt_short && strcmp( option->opt_short, argv ) == 0) ||
				(option->opt_long && strcmp( option->opt_long, argv ) == 0) )
			{
				result = option;
			}
		}
		else // wildcard option
		{
			if( option->opt_short == NULL && option->opt_long == NULL )
			{
				result = option;
			}
		}
	}

	return result;
}


bool cmd_opt_nop( const char* arguments[], size_t count, void* user_data )
{
	return true;
}
