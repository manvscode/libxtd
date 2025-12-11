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
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "xtd/memory.h"
#include "xtd/filesystem.h"

const char* file_size_string(const char* path, bool use_base_two, int precision)
{
    int64_t size = file_size(path);
    return size_in_best_unit((size_t) (size >= 0 ? size : 0), use_base_two, precision);
}

bool file_copy(const char* src_path, const char* dst_path)
{
    FILE* src_file = NULL;
    FILE* dst_file = NULL;
    char buffer[ 4096 ];

    src_file = fopen(src_path, "rb");

    if (!src_path)
    {
        return false;
    }

    dst_file = fopen(dst_path, "wb");

    if (!dst_path)
    {
        return false;
    }

    while (!feof(src_file))
    {
        size_t bytes_read    = fread(buffer, sizeof(char), sizeof(buffer), src_file);
        size_t bytes_written = 0;

        while (bytes_read - bytes_written > 0)
        {
            bytes_written += fwrite(buffer + bytes_written, sizeof(char), bytes_read - bytes_written, dst_file);
        }
    }

    fclose(src_file);
    fclose(dst_file);

    return true;
}

const char* file_extension(const char* filename)
{
    const char* extension = strrchr(filename, '.');

    if (!extension)
    {
        return NULL;
    }
    else
    {
        extension += 1;

        if (!extension)
        {
            return NULL;
        }
    }

    return extension;
}

char* file_slurp(const char* path, size_t *size)
{
    FILE* file = fopen(path, "r");
    char* result = NULL;

    if (file)
    {
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file); /* TODO: what if size is 0 */
        fseek(file, 0, SEEK_SET);

        if (file_size > 0)
        {
            *size = file_size + 1;
            result = (char*) malloc(sizeof(char) * (*size));

            if (result)
            {
                char* buffer = result;
                long sz      = file_size;

                while (!feof(file) && sz > 0)
                {
                    size_t bytes_read = fread(buffer, sizeof(char), sz, file);
                    buffer += bytes_read;
                    sz   -= bytes_read;
                }

                result[ *size - 1 ] = '\0';
            }
        }

        fclose(file);
    }

    return result;
}

int file_readline(FILE* stream, char* buffer, size_t size)
{
    if (size == 0)
    {
        return -1;
    }

    if (fgets(buffer, size, stream) == NULL)
    {
        return -1;  // EOF and nothing read
    }

    size_t len = strlen(buffer);

    // Check if we got a full line (newline present)
    if (buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';   // remove newline
        return len;    // return number of chars read
    }

    // No newline: could be EOF or truncation
    // Read until newline or EOF to maintain correct stream position
    int c = getc(stream);
    while (c != EOF && c != '\n')
    {
        c = getc(stream);
    }

    if (c == '\n')
    {
        // Truncated; buffer was not large enough.
        return -2;
    }

    // Not truncated; last line without newline
    return (int) len;
}

const char* basename(const char* path, char dir_separator)
{
#if 1
    const char *base = path;

    while (*path)
    {
        if (*path++ == dir_separator)
        {
            base = path;
        }
    }

    return base;
#else
    const char* basename = strrchr(path, dir_separator);
    return basename ? basename + 1 : path;
#endif
}

char* __path_r(const char* path, char dir_separator, char* buffer, size_t size) /* returns NULL on error  */
{
    char* p     = (char*) path;
    char *slash = NULL;
    //ssize_t length  = 0;
    size_t length  = 0;

    while (*p)
    {
        if (*p == dir_separator)
        {
            slash = p;
        }

        p++;
    }

    if (slash)
    {
        if (path == slash)
        {
            length = 1;
        }
        else
        {
            length = slash - path;
        }
    }
    else
    {
        length = p - path;
    }

    char* result = NULL;

    if (size >= (length + 1))
    {
        strncpy(buffer, path, length);
        buffer[ length ] = '\0';
        result = buffer;
    }

    return result;
}

char* __path(const char* path, char dir_separator) /* allocates memory */
{
    char* p     = (char*) path;
    char *slash = NULL;
    //ssize_t length  = 0;
    size_t length  = 0;

    while (*p) // find the last dir_separator
    {
        if (*p == dir_separator)
        {
            slash = p;
        }

        p++;
    }

    if (slash)
    {
        if (path == slash)
        {
            length = 1;
        }
        else
        {
            length = slash - path;
        }
    }
    else
    {
        length = p - path;
    }

    char* result = malloc(length + 1);

    if (result)
    {
        strncpy(result, path, length);
        result[ length ] = '\0';
    }

    return result;
}
