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
#ifndef _XTD_CMDOPT_H_
#define _XTD_CMDOPT_H_
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 * structure).
 */
typedef bool (*cmd_opt_handler_t) ( void* user_data, const char* arguments[], size_t count );

/*
 * A callback for handling an errors when processing options.
 */
typedef void (*cmd_opt_error_t) ( void* user_data, cmd_opt_result_t error, const char* opt );

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
		cmd_opt_error_t on_error, void* user_data );

/*
 * Print out the command-line help for the options to stdout.
 */
void cmd_opt_help( const cmd_opt_t* options, size_t option_count );

/*
 * Search for a matching option. Returns NULL if no matching option is found.
 */
const cmd_opt_t* cmd_opt_find( const cmd_opt_t* options, size_t option_count, const char* argv );

/*
 * A convenience for a options's no-operation behavioour. Useful for
 * temporarily ignoring an option.
 */
bool cmd_opt_nop( void* user_data, const char* arguments[], size_t count );

#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
	using ::cmd_opt_result_t;
	using ::cmd_opt_handler_t;
	using ::cmd_opt_error_t;
	using ::cmd_opt_t;
	using ::cmd_opt_process;
	using ::cmd_opt_help;
	using ::cmd_opt_nop;
} /* namespace */
#endif
#endif /* _XTD_CMDOPT_H_ */
