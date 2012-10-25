#AM_CFLAGS = $(DEPS_CFLAGS) -I../src/ -L../src/ -L.
AM_CFLAGS = -std=gnu99 -Wall -pedantic -g -ggdb -O0 -DDEBUG -I../src/ -L../src/ -L. -L../lib/ -L/usr/local/lib
LDADD     = -lutility -lm -lcollections



bin_PROGRAMS = \
test-exceptions \
test-huffman \
test-scrambling 

test_exceptions_SOURCES    = test-exceptions.c
test_huffman_SOURCES       = test-huffman.c
test_scrambling_SOURCES    = test-scrambling.c
