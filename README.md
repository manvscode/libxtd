# libxtd
A extension to the standard C library. This library aims to provide additional
functionality for projects using C.

## Building

### Linux
Building requires Autotools.

1. `apt install -y autoconf automake libtool`
1. `autoreconf -i`
1. `./configure`
1. `make`
1. `make install`

### MacOS X
Building requires Homebrew and Autotools.
1. `brew install autoconf automake libtool`
1. `autoreconf -i`
1. `./configure`
1. `make`
1. `make install`

### Cross-compiling for Windows with MinGW

1. `autoreconf -i`
1. Run the configure script for the host architecture:
	* For x86: `./configure --host=i686-w64-mingw32`
	* For x86_64: `./configure --host=x86_64-w64-mingw32`
1. `make`
1. `make install`

## Features
* Reference Counted Pointers
* Command-line argument acquisition.
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
* **<xtd/all.h>** -- a convenience header that will include all headers.
* **<xtd/checksums.h>** -- this is where various checksums can be found.
* **<xtd/console.h>** -- this is the console formatting and colorization.
* **<xtd/encoding.h>** -- this is where various encoding and compression code is.
* **<xtd/encryption.h>** -- this is where encryption can be found.
* **<xtd/endian.h>** -- this is where endian related code is.
* **<xtd/exceptions.h>** -- ***deprecated***; do not use.
* **<xtd/filesystem.h>** -- this is where cross-platform file and directory functionality is.
* **<xtd/floating-point.h>** -- this is where floating point related functionality is.
* **<xtd/memory.h>** -- this is where various memory related functions can be found.
* **<xtd/refobj.h>** -- this is reference counted pointers for heap allocated objects.
* **<xtd/string.h>** -- this is various string functions can be found.
* **<xtd/test.h>** -- this is the unit-testing framework.
* **<xtd/time.h>** -- this is where cross-platform time related functions can be found.

## License
    Copyright (C) 2010-2020 Joseph A. Marrero.  http://www.manvscode.com/
    
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
