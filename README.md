# libutility
A collection of utility code for projects using C/C++.

## Building

### Linux
1. `autoreconf -i`
2. `./configure`
3. `make`
4. `make install`

### Cross-compiling for Windows with MinGW

1. `autoreconf -i`
2. Run the configure script for the host architecture:
* For x86: `./configure --host=i686-w64-mingw32`
* For x86_64: `./configure --host=x86_64-w64-mingw32`
3. `make`
4. `make install`

## Features
* Reference Counted Pointers
* Cross-platform file IO.
* Memory size string formatting.
* Checksums and hashes (Java Hash, 8-bit XOR, Adler32, Fletcher16, and Fletcher32).
* Compression and encoding (Huffman, and base64).
* String manipulation, duplication, tokenizing, multi-byte strings.
* Buffer manipulations (bit rotations, big-encoding, swapping, xor, byte to binary, scrambling)
* IEEE-754 floating point equality tests.
* Cross-platform timing functions.
* Timezone conversion.
* ISO-8601 formating.
* Bit testing and manipulation.
* Caesar-cypher.
* Console colors and formating.
* Unit-test framework (see test.h)

## Header Files
* utility.h -- this is where most of the utility functions reside.
* console.h -- this is the console formatting and colorization.
* test.h -- this is the unit-testing framework.

## License
    Copyright (C) 2010-2014 Joseph A. Marrero.  http://www.manvscode.com/
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
