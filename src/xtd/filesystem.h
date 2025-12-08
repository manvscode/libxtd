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
#ifndef _XTD_FILESYSTEM_H_
#define _XTD_FILESYSTEM_H_
#include <stdlib.h>
#include <stdio.h>
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(_MSC_VER) && _MSC_VER >= 0)
# include <stdbool.h>
# include <stdint.h>
#else
# error "Need a C99 compiler."
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool        file_exists              (const char* path);
bool        file_is_writeable        (const char* path);
bool        file_is_readable         (const char* path);
bool        file_is_executable       (const char* path);
bool        file_copy                (const char* src_path, const char* dst_path);
bool        file_delete              (const char* path);
int64_t     file_size                (const char* path);
const char* file_size_string         (const char* path, bool use_base_two, int precision);
int64_t     file_age                 (const char* path); /* returns -1 on error */
const char* file_basename            (const char* path);
const char* file_extension           (const char* filename);
char*       file_slurp               (const char* path, size_t* size); /* allocates memory */
int         file_readline            (FILE* stream, char* buffer, size_t size);
bool        is_file                  (const char* path);

typedef enum directory_enumerate_mode {
    ENUMERATE_FILES,
    ENUMERATE_DIRECTORIES,
    ENUMERATE_ALL
} directory_enumerate_mode_t;
typedef void (*file_enumerate_fxn_t) (const char* filename, void* args);

bool        is_directory             (const char* path);
bool        directory_exists         (const char* path);
bool        directory_create         (const char* path);
bool        directory_delete         (const char* path, bool recursive);
char*       directory_path_r         (const char* _path, char* buffer, size_t size); /* returns NULL on error */
char*       directory_path           (const char* path); /* allocates memory */
void        directory_enumerate      (const char* path, bool recursive, directory_enumerate_mode_t mode, file_enumerate_fxn_t process_file, void* args);

#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
    using ::file_exists;
    using ::file_is_writeable;
    using ::file_is_readable;
    using ::file_is_executable;
    using ::file_copy;
    using ::file_delete;
    using ::file_size;
    using ::file_size_string;
    using ::file_age;
    using ::file_basename;
    using ::file_slurp;
    using ::file_readline;
    using ::is_file;
    using ::directory_enumerate_mode_t;
    using ::file_enumerate_fxn_t;
    using ::is_directory;
    using ::directory_exists;
    using ::directory_create;
    using ::directory_delete;
    using ::directory_path_r;
    using ::directory_path;
    using ::directory_enumerate;
} /* namespace */
#endif
#endif /* _XTD_FILESYSTEM_H_ */
