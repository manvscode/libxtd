/*
 * Copyright (C) 2010-2025 by Joseph A. Marrero. http://www.manvscode.com/
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
#include <stdbool.h>
#include <string.h>

void bubble_sort(void *base, size_t nel, size_t width, int (*compare)(const void *, const void *))
{
    if (nel >= 2)
    {
        bool swapped = true;

        while (swapped)
        {
            swapped = false;
            for (size_t i = 1; i < nel; i++)
            {
                void* left  = ((unsigned char*)base) + (i   ) * width;
                void* right = ((unsigned char*)base) + (i - 1) * width;

                if (compare(left, right) < 0)
                {
                    unsigned char tmp[ width ];

                    memcpy(tmp, left, width);
                    memcpy(left, right, width);
                    memcpy(right, tmp, width);

                    swapped = true;
                }
            }
        }
    }
}
