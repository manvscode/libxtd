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
#ifndef _XTD_REFOBJ_H_
#define _XTD_REFOBJ_H_
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*refobj_destroy_fxn_t) ( void* ptr );

/*
 * Reference Counting
 */
void* refobj_alloc   ( size_t size, refobj_destroy_fxn_t destroy );
void  refobj_retain  ( void* obj );
void  refobj_release ( void* obj );

#ifdef __cplusplus
} /* extern "C" */
namespace xtd {
	using ::refobj_destroy_fxn_t;
	using ::refobj_alloc;
	using ::refobj_retain;
	using ::refobj_release;
} /* namespace */
#endif
#endif /* _XTD_REFOBJ_H_ */
