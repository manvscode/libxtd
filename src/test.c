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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <xtd/console.h>
#include <xtd/string.h>
#include <xtd/time.h>
#include <xtd/floating-point.h>
#include <xtd/test.h>

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__MINGW64)
# define COLOR_BEGIN(bg,fg)                    ""
# define COLOR_END                             ""
# define COLOR_TOKEN(color_bg, color_fg, tok)  COLOR_BEGIN(color_bg, color_fg) #tok COLOR_END
# define COLOR_STRING(color_bg, color_fg, str) COLOR_BEGIN(color_bg, color_fg) str COLOR_END

# define COLOR_GREEN                           COLOR_BEGIN(0,32)
# define COLOR_RED                             COLOR_BEGIN(0,31)
# define COLOR_BRIGHT_RED                      ""
# define COLOR_YELLOW                          COLOR_BEGIN(0,33)
# define COLOR_BLUE                            COLOR_BEGIN(0,34)
# define COLOR_MAGENTA                         COLOR_BEGIN(0,35)
# define COLOR_CYAN                            COLOR_BEGIN(0,36)
# define COLOR_WHITE                           COLOR_BEGIN(0,37)

# define COLOR_GREEN_STR(s)                    COLOR_STRING(0,32,s)
# define COLOR_YELLOW_STR(s)                   COLOR_STRING(0,33,s)
# define COLOR_RED_STR(s)                      COLOR_STRING(0,31,s)
# define COLOR_CYAN_STR(s)                     COLOR_STRING(0,36,s)

# define CORNER_TL "+"
# define CORNER_TR "+"
# define CORNER_BL "+"
# define CORNER_BR "+"
# define INTERSECTION_L "+"
# define INTERSECTION_R "+"
# define INTERSECTION_T "+"
# define INTERSECTION_B "+"
# define INTERSECTION_C "+"
# define HORIZONTAL_BAR "-"
# define VERTICAL_BAR "|"
# define BULLET "*"
# define CHECKMARK "y"
# define XMARK     "n"
#else
# define COLOR_BEGIN(bg,fg)                    "\033[" #bg ";" #fg "m"
# define COLOR_END                             "\033[m"
# define COLOR_TOKEN(color_bg, color_fg, tok)  COLOR_BEGIN(color_bg, color_fg) #tok COLOR_END
# define COLOR_STRING(color_bg, color_fg, str) COLOR_BEGIN(color_bg, color_fg) str COLOR_END

# define COLOR_GREEN                           COLOR_BEGIN(0,32)
# define COLOR_RED                             COLOR_BEGIN(0,31)
# define COLOR_BRIGHT_RED                      "\033[9;1m"
# define COLOR_YELLOW                          COLOR_BEGIN(0,33)
# define COLOR_BLUE                            COLOR_BEGIN(0,34)
# define COLOR_MAGENTA                         COLOR_BEGIN(0,35)
# define COLOR_CYAN                            COLOR_BEGIN(0,36)
# define COLOR_WHITE                           COLOR_BEGIN(0,37)

# define COLOR_GREEN_STR(s)                    COLOR_STRING(0,32,s)
# define COLOR_YELLOW_STR(s)                   COLOR_STRING(0,33,s)
# define COLOR_RED_STR(s)                      COLOR_STRING(0,31,s)
# define COLOR_CYAN_STR(s)                     COLOR_STRING(0,36,s)

# define CORNER_TL "\u250c"
# define CORNER_TR "\u2510"
# define CORNER_BL "\u2514"
# define CORNER_BR "\u2518"
# define INTERSECTION_L "\u251c"
# define INTERSECTION_R "\u2524"
# define INTERSECTION_T "\u252c"
# define INTERSECTION_B "\u2534"
# define INTERSECTION_C "\u253c"
# define HORIZONTAL_BAR "\u2500"
# define VERTICAL_BAR "\u2502"
# define BULLET "\u2022"
# define CHECKMARK "\u2713"
# define XMARK     "\u2718"
#endif


#define COL1_WIDTH  8
#define COL2_WIDTH  69
#define WIDTH  (1 + COL1_WIDTH + 1 + COL2_WIDTH + 1)

bool test_nil(test_ctx_t* ctx)
{
    return false;
}

void test_wait_for_true(const bool* flag, int timeout)
{
    double start = time_milliseconds();
    double elapsed = 0.0;

    while (!*flag && elapsed < timeout)
    {
        time_msleep(10);
        elapsed = time_milliseconds() - start;
    }
}

void test_wait_for_int(const int* n, int value, int timeout)
{
    double start = time_milliseconds();
    double elapsed = 0.0;

    while (*n != value && elapsed < timeout)
    {
        time_msleep(10);
        elapsed = time_milliseconds() - start;
    }
}

struct test_ctx {
    char* message;
};

static bool test_feature(unsigned int i, const char* feature, test_fxn_t test)
{
    test_ctx_t ctx = (test_ctx_t) {
        .message = NULL,
    };
    bool is_passed = test(&ctx);

    char description[ COL2_WIDTH ];

    size_t len = strlen(feature);

    if (len > sizeof(description)) len = sizeof(description);

    memcpy(description, feature, len);
    memset(description + len, ' ', sizeof(description) - len);
    description[ sizeof(description) - 1 ] = '\0';

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf(VERTICAL_BAR);
    console_reset(stdout);

    console_fg_color_8(stdout, CONSOLE_COLOR8_CYAN);
    printf("%7u ", i);
    console_reset(stdout);

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf("%s", VERTICAL_BAR);
    console_reset(stdout);

    if (is_passed)
    {
        console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_GREEN);
        printf(" %s", CHECKMARK);
        console_reset(stdout);
    }
    else
    {
        console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_RED);
        printf(" %s", XMARK);
        console_reset(stdout);
    }

    printf(" %-*.*s ", COL2_WIDTH - 3 - 1, COL2_WIDTH - 3 - 1, description);
    /*
       if (is_passed)
       {
       console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_GREEN);
       printf("%s ", CHECKMARK);
       console_reset(stdout);
       }
       else
       {
       console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_RED);
       printf("%s ", XMARK);
       console_reset(stdout);
       }
       */

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf("%s", VERTICAL_BAR);
    console_reset(stdout);
    printf("\n");

    if (ctx.message)
    {
        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);

        printf("%*.*s", COL1_WIDTH, COL1_WIDTH, "");

        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);

        printf("   %s ", BULLET);

        console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_RED);
        printf("%-*.*s", COL2_WIDTH - 5, COL2_WIDTH - 5, ctx.message);
        console_reset(stdout);

        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);

        printf("\n");

        free(ctx.message);
    }

    return is_passed;
}



size_t test_features(const char* description, const test_case_t cases[], size_t count, bool continue_on_failure)
{
    size_t pass_count = 0;
    int len;

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf(CORNER_TL);
    len = COL1_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(INTERSECTION_T);
    len = COL2_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(CORNER_TR);
    console_reset(stdout);
    printf("\n");


    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf("%s", VERTICAL_BAR);
    console_reset(stdout);

    console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_CYAN);
    printf("   Cases");
    console_reset(stdout);

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf("%s", VERTICAL_BAR);
    console_reset(stdout);

    console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_YELLOW);
    printf(" %-*.*s ", COL2_WIDTH - 2, COL2_WIDTH - 2, description);
    console_reset(stdout);

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf("%s", VERTICAL_BAR);
    console_reset(stdout);

    printf("\n");

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf(INTERSECTION_L);
    len = COL1_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(INTERSECTION_C);
    len = COL2_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(INTERSECTION_R);
    console_reset(stdout);
    printf("\n");

    for (size_t i = 0; i < count; i++)
    {
        bool is_passed = test_feature(i + 1, cases[ i ].description, cases[ i ].test);

        if (is_passed)
        {
            pass_count += 1;
        }
        else if (!continue_on_failure)
        {
            break;
        }
    }

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf(INTERSECTION_L);
    len = COL1_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(INTERSECTION_C);
    len = COL2_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(INTERSECTION_R);
    console_reset(stdout);
    printf("\n");


    if (continue_on_failure)
    {
        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);

        console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_CYAN);
        printf(" Results");
        console_reset(stdout);

        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);

        size_t fail_count = count - pass_count;

        int sz = 0;
        sz += printf(" ");
        if (pass_count > 0)
        {
            console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_GREEN);
            sz += printf("%zu passed", pass_count);
            console_reset(stdout);
            if (fail_count > 0)
            {
                sz += printf(", ");
            }
        }

        if (fail_count > 0)
        {
            console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_RED);
            sz += printf("%zu failed", fail_count);
            console_reset(stdout);
        }
        sz += printf(".");

        printf(" %*.*s ", COL2_WIDTH - sz - 2, COL2_WIDTH - sz - 2, "");

        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);
        printf("\n");

    }
    else
    {
        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf("%s", VERTICAL_BAR);
        console_reset(stdout);

        console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_CYAN);
        printf(" Results");
        console_reset(stdout);

        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf("%s", VERTICAL_BAR);
        console_reset(stdout);

        if (pass_count == count)
        {
            console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_GREEN);
            printf(" %-*.*s ", COL2_WIDTH - 2, COL2_WIDTH - 2, "Passed!");
            console_reset(stdout);
        }
        else
        {
            console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_RED);
            printf(" %-*.*s ", COL2_WIDTH - 2, COL2_WIDTH - 2, "Failed!");
            console_reset(stdout);
        }

        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf("%s", VERTICAL_BAR);
        console_reset(stdout);

        printf("\n");
    }

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf(CORNER_BL);
    len = COL1_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(INTERSECTION_B);
    len = COL2_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(CORNER_BR);
    console_reset(stdout);
    printf("\n");

    return pass_count;
}


bool test_suites(const test_suite_t suites[], size_t count, size_t* p_pass_count, size_t* p_fail_count)
{
    size_t pass_count = 0;
    size_t total_count = 0;
    int len;

    for (size_t i = 0; i < count; i++)
    {
        const char* description  = suites[ i ].get_description();
        const size_t count       = suites[ i ].get_count();
        const test_case_t* cases = suites[ i ].get_cases();

        pass_count += test_features(description, cases, count, true);
        total_count += count;
        printf("\n");
    }

    printf("\n");

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf(CORNER_TL);
    len = COL1_WIDTH + 1;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    len = COL2_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(CORNER_TR);
    console_reset(stdout);
    printf("\n");


    {
        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);
        printf(" ");

        int pass_percentage = (int) ((100.0f * pass_count) / total_count);
        int fail_percentage = 100 - pass_percentage;

        int sz = 0;
        //console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_CYAN);
        sz += printf("Out of %zu tests", total_count);
        //console_reset(stdout);
        sz += printf(", ");

        console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_GREEN);
        sz += printf("%d%% passed", pass_percentage);
        console_reset(stdout);
        sz += printf(", and ");

        console_fg_color_8(stdout, CONSOLE_COLOR8_BRIGHT_RED);
        sz += printf("%d%% failed", fail_percentage);
        console_reset(stdout);
        sz += printf(".");

        printf("%*.*s", WIDTH - sz - 3, WIDTH - sz - 3, "");
        console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
        printf(VERTICAL_BAR);
        console_reset(stdout);

        printf("\n");
    }

    console_fg_color_8(stdout, CONSOLE_COLOR8_GREY_10);
    printf(CORNER_BL);
    len = COL1_WIDTH + 1;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    len = COL2_WIDTH;
    while (len-- > 0) printf(HORIZONTAL_BAR);
    printf(CORNER_BR);
    console_reset(stdout);
    printf("\n");

    if (p_pass_count)
    {
        *p_pass_count = pass_count;
    }

    if (p_fail_count)
    {
        *p_fail_count = total_count - pass_count;
    }

    return pass_count == total_count;
}

bool test_assert_true(test_ctx_t* ctx, bool expression, const char* message, ...)
{
    if (!expression)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }

    return expression;
}

bool test_assert_not_null(test_ctx_t* ctx, const void* p, const char* message, ...)
{
    if (!p)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }

    return p != NULL;

}

bool test_assert_pointer_equals(test_ctx_t* ctx, const void* a, const void* b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;

}

bool test_assert_memory_equals(test_ctx_t* ctx, const void* a, const void* b, size_t size, const char* message, ...)
{
    bool result = memcmp(a, b, size) == 0;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;

}

bool test_assert_string_equals(test_ctx_t* ctx, const char* a, const char* b, const char* message, ...)
{
    bool result = a && b && strcmp(a, b) == 0;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_char_equals(test_ctx_t* ctx, char a, char b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_unsigned_char_equals(test_ctx_t* ctx, unsigned char a, unsigned char b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_short_equals(test_ctx_t* ctx, short a, short b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_unsigned_short_equals(test_ctx_t* ctx, unsigned short a, unsigned short b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_int_equals(test_ctx_t* ctx, int a, int b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_unsigned_int_equals(test_ctx_t* ctx, unsigned int a, unsigned int b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_long_equals(test_ctx_t* ctx, long a, long b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_long_long_equals(test_ctx_t* ctx, long long a, long long b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_unsigned_long_equals(test_ctx_t* ctx, unsigned long a, unsigned long b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_unsigned_long_long_equals(test_ctx_t* ctx, unsigned long long a, unsigned long long b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_float_equals(test_ctx_t* ctx, float a, float b, const char* message, ...)
{
    bool result = float_is_equal(a, b);
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_double_equals(test_ctx_t* ctx, double a, double b, const char* message, ...)
{
    bool result = double_is_equal(a, b);
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_long_double_equals(test_ctx_t* ctx, long double a, long double b, const char* message, ...)
{
    bool result = long_double_is_equal(a, b);
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

bool test_assert_size_equals(test_ctx_t* ctx, size_t a, size_t b, const char* message, ...)
{
    bool result = a == b;
    if (!result)
    {
        va_list args;
        va_start(args, message);
        char formatted_msg[512];
        vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
        formatted_msg[ sizeof(formatted_msg) - 1 ] = '\0';
        va_end(args);

        if (!ctx->message)
        {
            ctx->message = string_dup(formatted_msg);
        }
    }
    return result;
}

