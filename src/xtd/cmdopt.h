/*
 * Copyright (C) 2010-2025 by Joseph A. Marrero. https://joemarrero.com/
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
#ifndef _XTD_CMDOPT_H_
#define _XTD_CMDOPT_H_
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
# include <stdint.h>
#else
# error "Need a C99 compiler."
#endif
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cmd_opt_ctx;
typedef struct cmd_opt_ctx cmd_opt_ctx_t;

/*
 * Returns the number of strings returned by the cmd_opt_argv() function.
 * This is equivalent to the argc passed to cmd_opt_process(). This should
 * be equivalent to the argc in main(int argc, char* argv[]).
 */
int cmd_opt_argc( const cmd_opt_ctx_t* ctx );

/*
 * Returns a point to the argument strings passed to cmd_opt_process(). This
 * should be equivalent to the argv in main(int argc, char* argv[]).
 */
const char** cmd_opt_argv( const cmd_opt_ctx_t* ctx );

/*
 * Returns the number of arguments that the option is expecting.
 */
size_t cmd_opt_args_count( const cmd_opt_ctx_t* ctx );

/*
 * Returns a point to the first argument.
 */
const char** cmd_opt_args( const cmd_opt_ctx_t* ctx );

/*
 * When calling cmd_opt_process() it is possible that an error can occur. These
 * are the possible error coded that cmd_opt_process() can return and the error
 * code that will be passed to the error handler (see cmd_opt_error_t).
 */
typedef enum cmd_opt_result {
	CMD_OPT_SUCCESS               = (0),
	CMD_OPT_ERR_NO_OPTIONS        = (-1),
	CMD_OPT_ERR_UNEXPECTED_OPTION = (-2),
	CMD_OPT_ERR_INVALID_ARG_COUNT = (-3),
	CMD_OPT_ERR_ABORTED           = (-4)
} cmd_opt_result_t;

/*
 * A callback for handling a commmand option's arguments (see the cmd_opt_t
 * structure). Return true if the arguments can be handled. Otherwise, return
 * false and abort the processing of the remaining command line options.
 */
typedef bool (*cmd_opt_handler_t) ( const cmd_opt_ctx_t* ctx, void* user_data );

/*
 * A callback for handling an errors when processing options.
 */
typedef void (*cmd_opt_error_t) ( cmd_opt_result_t error, const char* opt, void* user_data );

/*
 * A structure that defines an accepted command line option.
 */
typedef struct cmd_opt {
	const char* opt_short; // The option's short form (i.e. "-h").
	const char* opt_long; // The option's long form (i.e. "--help").
	const int opt_arg_count; // How many arguments are expected to follow.
	const char* opt_description; // A description of the option.
	cmd_opt_handler_t callback; // Set to cmd_opt_nop() for ignoring an option.
} cmd_opt_t;

/*
 * Process all of the command line options that were passwed to the program.
 * Several possible errors are possible when processing options so the on_error
 * callback can be called.
 *
 * This function returns 0 on success, and a negative value on error (see the
 * various CMD_OPT_* constants).
 */
cmd_opt_result_t cmd_opt_process( int argc, char* argv[],
		const cmd_opt_t* options, size_t option_count,
		cmd_opt_error_t on_error, cmd_opt_handler_t on_unexpected,
		void* user_data );

/*
 * Print out the command-line help for the options to stdout.
 */
void cmd_opt_print_help( const cmd_opt_t* options, size_t option_count );

/*
 * Search for a matching option. Returns NULL if no matching option is found.
 * This is useful if you need to find the cmd_opt_t when inside a callback but
 * do not want to assume any hard-coded data.
 */
const cmd_opt_t* cmd_opt_find( const cmd_opt_t* options, size_t option_count, const char* argv );

/*
 * A convenience for a options's no-operation behavioour. Useful for
 * temporarily ignoring an option.
 */
bool cmd_opt_nop( const char* arguments[], size_t count, void* user_data );

#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
	using ::cmd_opt_result_t;
	using ::cmd_opt_handler_t;
	using ::cmd_opt_error_t;
	using ::cmd_opt_t;
	using ::cmd_opt_process;
	using ::cmd_opt_print_help;
	using ::cmd_opt_nop;
} /* namespace */
#endif
#endif /* _XTD_CMDOPT_H_ */
