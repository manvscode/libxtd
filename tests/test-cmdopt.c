/*
 * Copyright (C) 2014 by Joseph A. Marrero. http://www.manvscode.com/
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
#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS
#endif
#include <stdbool.h>
#include "xtd/cmdopt.h"
#include "xtd/test.h"


static bool test_cmd_opt_process( test_ctx_t* ctx );
static bool test_cmd_opt_find( test_ctx_t* ctx );


const char* CMDOPT_TEST_DESCRIPTION = "Testing functions in <xtd/cmdopt.h>";
const test_case_t CMDOPT_TEST_CASES[] = {
	{ "Test cmd_opt_process()", test_cmd_opt_process },
	{ "Test cmd_opt_find()", test_cmd_opt_find },
};
const size_t CMDOPT_TEST_COUNT = sizeof(CMDOPT_TEST_CASES) / sizeof(CMDOPT_TEST_CASES[0]);

typedef struct {
	const char* f;
	const char* o[3];
	bool v;
} test_cmd_opt_process_state_t;

static bool test_cmd_opt_process_f( const cmd_opt_ctx_t* ctx, void* user_data )
{
	test_cmd_opt_process_state_t* state = (test_cmd_opt_process_state_t*) user_data;
	const char** arguments = cmd_opt_args( ctx );
	size_t count = cmd_opt_args_count( ctx );
	state->f = arguments[0];
	return count == 1;
}

static bool test_cmd_opt_process_o( const cmd_opt_ctx_t* ctx, void* user_data )
{
	test_cmd_opt_process_state_t* state = (test_cmd_opt_process_state_t*) user_data;
	const char** arguments = cmd_opt_args( ctx );
	size_t count = cmd_opt_args_count( ctx );
	state->o[0] = arguments[0];
	state->o[1] = arguments[1];
	state->o[2] = arguments[2];
	return count == 3;
}

static bool test_cmd_opt_process_v( const cmd_opt_ctx_t* ctx, void* user_data )
{
	test_cmd_opt_process_state_t* state = (test_cmd_opt_process_state_t*) user_data;
	//const char** arguments = cmd_opt_args( ctx );
	size_t count = cmd_opt_args_count( ctx );
	state->v = true;
	return count == 0;
}

bool test_cmd_opt_process( test_ctx_t* ctx )
{
	bool result = true;
	int argc = 8;
	char* argv[] = {
		"program",
		"-f",
		"filename.txt",
		"-o",
		"o_1",
		"o_2",
		"o_3",
		"-v",
	};

	test_cmd_opt_process_state_t state = (test_cmd_opt_process_state_t) {
		.f = NULL,
		.o = { NULL, NULL, NULL },
		.v = false,
	};

	cmd_opt_t options[] = {
		{ "-f", "--file", 1, "Read File", test_cmd_opt_process_f },
		{ "-o", "--options", 3, "Read Options", test_cmd_opt_process_o },
		{ "-v", "--verbose", 0, "Toggle Verbose", test_cmd_opt_process_v }
	};
	size_t option_count = sizeof(options) / sizeof(options[0]);

	cmd_opt_result_t res = cmd_opt_process( argc, argv,
	                                        options, option_count,
											NULL, NULL, &state );
	if( !test_assert_true(ctx, res == CMD_OPT_SUCCESS, "Expected cmd_opt_process() to succeed (res = %d).", res) )
	{
		result = false;
		goto done;
	}

	if( !test_assert_equals(ctx, "filename.txt", state.f, "Expected f to be \"filename.txt\"") )
	{
		result = false;
		goto done;
	}

	if( !test_assert_equals(ctx, "o_1", state.o[0], "Expected o 1 to be \"o_1\"") )
	{
		result = false;
		goto done;
	}

	if( !test_assert_equals(ctx, "o_2", state.o[1], "Expected o 1 to be \"o_2\"") )
	{
		result = false;
		goto done;
	}

	if( !test_assert_equals(ctx, "o_3", state.o[2], "Expected o 1 to be \"o_3\"") )
	{
		result = false;
		goto done;
	}

	if( !test_assert_true(ctx, state.v, "Expected v to be true.") )
	{
		result = false;
		goto done;
	}
done:
	return result;
}

bool test_cmd_opt_find( test_ctx_t* ctx )
{
	bool result = true;
	cmd_opt_t options[] = {
		{ "-f", "--file", 1, "Read File", test_cmd_opt_process_f },
		{ "-o", "--options", 3, "Read Options", test_cmd_opt_process_o },
		{ "-v", "--verbose", 0, "Toggle Verbose", test_cmd_opt_process_v }
	};
	size_t option_count = sizeof(options) / sizeof(options[0]);

	const cmd_opt_t* opt = cmd_opt_find(options, option_count, "--file" );

	if( !test_assert_not_null( ctx, opt, "Expected opt to not be NULL" ) )
	{
		result = false;
		goto done;
	}

	if( !test_assert_equals( ctx, "-f", opt->opt_short, "Expected opt short-form to not be \"-f\"" ) )
	{
		result = false;
		goto done;
	}

	opt = cmd_opt_find(options, option_count, "-o" );
	if( !test_assert_not_null( ctx, opt, "Expected opt to not be NULL" ) )
	{
		result = false;
		goto done;
	}

	if( !test_assert_equals( ctx, "--options", opt->opt_long, "Expected opt long-form to not be \"--options\"" ) )
	{
		result = false;
		goto done;
	}

	opt = cmd_opt_find(options, option_count, "-v" );
	if( !test_assert_not_null( ctx, opt, "Expected opt to not be NULL" ) )
	{
		result = false;
		goto done;
	}

	if( !test_assert_equals( ctx, "--verbose", opt->opt_long, "Expected opt long-form to not be \"--verbose\"" ) )
	{
		result = false;
		goto done;
	}

	opt = cmd_opt_find(options, option_count, "-c" );
	if( !test_assert_true( ctx, opt == NULL, "Expected opt to be NULL" ) )
	{
		result = false;
		goto done;
	}

	opt = cmd_opt_find(options, option_count, "--foobar" );
	if( !test_assert_true( ctx, opt == NULL, "Expected opt to be NULL" ) )
	{
		result = false;
		goto done;
	}

done:
	return result;
}

#ifdef TEST_CMDOPT
int main(int argc, char* argv[])
{
	size_t pass_count = test_features( CMDOPT_TEST_DESCRIPTION, CMDOPT_TEST_CASES, CMDOPT_TEST_COUNT, true );
	return CMDOPT_TEST_COUNT - pass_count;
}
#endif
